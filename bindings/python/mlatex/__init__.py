"""Typeset LaTeX with the bundled mLaTeX system."""

from __future__ import annotations

import ctypes
import os
import sys
from pathlib import Path
from types import TracebackType
from typing import Callable, Optional, Union

__all__ = ["Session", "compose", "typeset", "snippet", "library"]

_Assets = Optional[Union[str, os.PathLike[str]]]
_Content = Union[str, bytes, bytearray, memoryview]
_Command = Callable[..., Optional[str]]

_folder = Path(__file__).parent
library = str(
    _folder / {"win32": "latex_ffi.dll", "darwin": "liblatex_ffi.dylib"}.get(
        sys.platform, "liblatex_ffi.so"
    )
)

_pointer = ctypes.c_void_p
_text = ctypes.c_char_p
_size = ctypes.c_size_t
_status = ctypes.c_int
_pdf = ctypes.POINTER(ctypes.c_ubyte)
_handler = ctypes.CFUNCTYPE(None, _pointer, ctypes.POINTER(_text), _size, _pointer)
_typeset = ctypes.CFUNCTYPE(
    _status, _pointer, _text, _size, ctypes.POINTER(_pdf), ctypes.POINTER(_size)
)


class _Latex(ctypes.Structure):
    # Keep this order in sync with include/protocols/ffi.hpp.
    _fields_ = [
        ("compose", ctypes.CFUNCTYPE(_pointer, _text)),
        ("dispose", ctypes.CFUNCTYPE(None, _pointer)),
        ("set", ctypes.CFUNCTYPE(_status, _pointer, _text, _text)),
        ("unset", ctypes.CFUNCTYPE(_status, _pointer, _text)),
        ("define", ctypes.CFUNCTYPE(_status, _pointer, _text, _size, _handler, _pointer)),
        ("forget", ctypes.CFUNCTYPE(_status, _pointer, _text)),
        ("write", ctypes.CFUNCTYPE(None, _pointer, _text, _size)),
        ("provide", ctypes.CFUNCTYPE(_status, _pointer, _text, _text, _size)),
        ("withdraw", ctypes.CFUNCTYPE(_status, _pointer, _text)),
        ("typeset", _typeset),
        ("error", ctypes.CFUNCTYPE(_text, _pointer)),
        ("offline", ctypes.CFUNCTYPE(_status, _pointer, _status)),
        ("snippet", _typeset),
    ]


def compose(assets: _Assets = None) -> Session:
    """Compose a session.

    Args:
        assets: Directory of fonts and other assets. None uses the bundled assets.
    """
    return Session(assets)


def typeset(document: str, *, assets: _Assets = None) -> bytes:
    """Return the PDF for a LaTeX document.

    Args:
        document: Complete LaTeX source, including the preamble.
        assets: Directory of fonts and other assets. None uses the bundled assets.

    Raises:
        RuntimeError: The session could not be composed or typesetting failed.
    """
    with compose(assets) as session:
        if not session.typeset(document):
            raise RuntimeError(session.error())
        return session.pdf()


def snippet(text: str, *, assets: _Assets = None) -> bytes:
    """Return the PDF for a piece of LaTeX on a page cropped to it.

    Args:
        text: LaTeX source without a preamble.
        assets: Directory of fonts and other assets. None uses the bundled assets.

    Raises:
        RuntimeError: The session could not be composed or typesetting failed.
    """
    with compose(assets) as session:
        if not session.snippet(text):
            raise RuntimeError(session.error())
        return session.pdf()


class Session:
    """Keep values, commands, files, and PDF output across documents."""

    def __init__(self, assets: _Assets = None) -> None:
        """Compose a session with the bundled assets or the given directory."""
        self._session: Optional[int] = None
        if sys.platform == "win32":
            with os.add_dll_directory(str(_folder)):
                self._native = ctypes.CDLL(library)
        else:
            self._native = ctypes.CDLL(library)
        entry = self._native.engine  # The exported C symbol.
        entry.argtypes = []
        entry.restype = ctypes.POINTER(_Latex)
        self._system = entry().contents
        self._handlers: dict[str, ctypes._CFuncPtr] = {}
        self._pdf = b""
        self._running = False
        self._failure: Optional[BaseException] = None

        directory = None if assets is None else os.fsdecode(assets).encode("utf-8")
        if directory is not None and b"\0" in directory:
            raise ValueError("Asset path contains a null character")
        self._session = self._system.compose(directory)
        if not self._session:
            raise RuntimeError(
                "Could not compose an mLaTeX session. Check the assets directory."
            )

    def _handle(self) -> int:
        if self._running:
            raise RuntimeError("The session is already typesetting")
        if self._session is None:
            raise RuntimeError("The session has been disposed")
        return self._session

    def dispose(self) -> None:
        """Dispose of the session. Repeated calls have no effect."""
        if self._session is None:
            return
        session = self._handle()
        self._session = None
        self._system.dispose(session)
        self._handlers.clear()
        self._pdf = b""

    def __enter__(self) -> Session:
        self._handle()
        return self

    def __exit__(
        self,
        exception_type: Optional[type[BaseException]],
        exception: Optional[BaseException],
        traceback: Optional[TracebackType],
    ) -> None:
        self.dispose()

    def __del__(self) -> None:
        if getattr(self, "_session", None) is not None:
            self.dispose()

    def set(self, name: str, value: str) -> bool:
        """Set a value read by a LaTeX variable.

        Args:
            name: Variable name.
            value: Text to substitute for the variable.
        """
        if "\0" in name or "\0" in value:
            raise ValueError("Variable name and value cannot contain null characters")
        return bool(
            self._system.set(self._handle(), name.encode("utf-8"), value.encode("utf-8"))
        )

    def unset(self, name: str) -> bool:
        """Take back the variable named by ``name``."""
        if "\0" in name:
            raise ValueError("Variable name contains a null character")
        return bool(self._system.unset(self._handle(), name.encode("utf-8")))

    def define(self, name: str, arity: int, handler: _Command) -> bool:
        """Define a LaTeX command.

        Args:
            name: Command name, with an optional leading backslash.
            arity: Number of arguments, from zero to nine.
            handler: Receives expanded arguments and returns LaTeX text or None.
        """
        session = self._handle()
        name = name.removeprefix("\\")
        if not name or name.startswith("\\") or "\0" in name or not 0 <= arity <= 9:
            raise ValueError("A command needs a valid name and an arity from 0 to 9")
        if not callable(handler):
            raise TypeError("The command handler must be callable")

        @_handler
        def write(
            _data: Optional[int],
            arguments: ctypes.Array[bytes],
            count: int,
            output: int,
        ) -> None:
            if self._failure is not None:
                return
            try:
                result = handler(
                    *(arguments[index].decode("utf-8") for index in range(count))
                )
                if result is not None:
                    encoded = result.encode("utf-8")
                    self._system.write(output, encoded, len(encoded))
            except BaseException as failure:
                self._failure = failure

        if not self._system.define(session, name.encode("utf-8"), arity, write, None):
            return False
        self._handlers[name] = write
        return True

    def forget(self, name: str) -> bool:
        """Take back the command named by ``name``."""
        if "\0" in name:
            raise ValueError("Command name contains a null character")
        if not self._system.forget(self._handle(), name.encode("utf-8")):
            return False
        self._handlers.pop(name.removeprefix("\\"), None)
        return True

    def provide(self, name: str, content: _Content) -> bool:
        """Provide a file from memory.

        Args:
            name: Path as the LaTeX document refers to it.
            content: Text or binary data for the file.
        """
        if "\0" in name:
            raise ValueError("File name contains a null character")
        if isinstance(content, str):
            content = content.encode("utf-8")
        elif isinstance(content, (bytearray, memoryview)):
            content = bytes(content)
        if not isinstance(content, bytes):
            raise TypeError("File content must be text or bytes")
        return bool(
            self._system.provide(
                self._handle(), name.encode("utf-8"), content, len(content)
            )
        )

    def withdraw(self, name: str) -> bool:
        """Take back the file named by ``name``."""
        if "\0" in name:
            raise ValueError("File name contains a null character")
        return bool(self._system.withdraw(self._handle(), name.encode("utf-8")))

    def offline(self, on: bool = True) -> bool:
        """Disable document network requests when ``on`` is true."""
        return bool(self._system.offline(self._handle(), bool(on)))

    def typeset(self, document: str) -> bool:
        """Typeset a complete LaTeX document and report success."""
        session = self._handle()
        encoded = document.encode("utf-8")
        pdf = _pdf()
        size = _size()
        self._pdf = b""
        self._running = True
        try:
            made = self._system.typeset(
                session, encoded, len(encoded), ctypes.byref(pdf), ctypes.byref(size)
            )
            if pdf:
                self._pdf = ctypes.string_at(pdf, size.value)
        finally:
            self._running = False
            failure = self._failure
            self._failure = None
        if failure is not None:
            raise failure
        return bool(made)

    def snippet(self, text: str) -> bool:
        """Typeset LaTeX without a preamble and report success."""
        session = self._handle()
        encoded = text.encode("utf-8")
        pdf = _pdf()
        size = _size()
        self._pdf = b""
        self._running = True
        try:
            made = self._system.snippet(
                session, encoded, len(encoded), ctypes.byref(pdf), ctypes.byref(size)
            )
            if pdf:
                self._pdf = ctypes.string_at(pdf, size.value)
        finally:
            self._running = False
            failure = self._failure
            self._failure = None
        if failure is not None:
            raise failure
        return bool(made)

    def pdf(self) -> bytes:
        """Return an owned copy of the last PDF."""
        self._handle()
        return self._pdf

    def error(self) -> str:
        """Return the last typesetting diagnostics."""
        return self._system.error(self._handle()).decode("utf-8")

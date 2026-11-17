# mlatex for Python

Typeset LaTeX into PDF with the bundled mLaTeX engine and fonts.

```bash
python -m pip install mlatex
```

## Typeset a document

```python
import mlatex

document = r"""\documentclass{article}
\begin{document}
Hello, \LaTeX.
\end{document}
"""

pdf = mlatex.typeset(document)
with open("hello.pdf", "wb") as file:
    file.write(pdf)
```

Use `mlatex.snippet(text)` for a formula, table, or other piece of LaTeX.
Both calls return PDF bytes and raise `RuntimeError` with the engine's
diagnostics if typesetting fails. Pass `assets` to use a different assets directory.

## Session API

Compose a session to reuse values, commands, and files across documents.

```python
with mlatex.compose() as session:
    session.set("customer", "Acme")
    if not session.typeset(document):
        raise RuntimeError(session.error())
    pdf = session.pdf()
```

The `with` block disposes of the session on exit. You can also call
`session.dispose()` directly.

| Operation | What it does |
| --- | --- |
| `set(name, value)`, `unset(name)` | Set or take back a value read by `\variable{name}`. |
| `define(name, arity, handler)`, `forget(name)` | Define or take back a command. The handler receives each argument as a string and returns LaTeX text or `None`. |
| `provide(name, content)`, `withdraw(name)` | Provide or take back a file by the name the document uses. Content can be text or bytes. |
| `typeset(document)` | Typeset a full document and return whether it succeeded. |
| `snippet(text)` | Typeset a formula, table, or other piece of LaTeX on a page cropped to it. |
| `pdf()`, `error()` | Read the latest PDF and diagnostics. A failed typeset may still produce a PDF. |
| `offline(on=True)` | Keep the session's documents off the network. |
| `dispose()` | Dispose of the session. |

See [Embedding](https://github.com/modern-latex/mlatex#embedding)
for the C and C++ APIs.

mLaTeX is licensed under the GNU Affero General Public License, version 3.

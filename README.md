# mLaTeX

**A LaTeX typesetting engine, rewritten from the ground up in modern C++.**

mLaTeX (Modernized LaTeX) reads LaTeX as people already write it and turns it
into PDF with a single program. There is no TeX distribution behind it, no
format files, no package tree on disk and no auxiliary files between runs.
The lexer, macro expander, parser, line breaker, page builder, font shaper and
PDF writer are all part of one engine, written in C++26.

The language stays the same. A document written for pdfLaTeX, its preamble
included, is meant to compile unchanged. What changes is the machinery
underneath: the work LaTeX does with thousands of lines of TeX macros is done
once, in compiled code.

> **Status: pre-release.** mLaTeX is changing quickly. The `aot` target,
> which writes the PDF directly, is complete; the command line's `jit` target
> is accepted but does nothing yet, while its pieces are built in
> [`src/jit`](src/jit/implementation.md). A package that loads is not yet a
> promise that every feature of it is drawn exactly, so check the PDF before
> you rely on it.

## Highlights

- **Reads existing LaTeX.** 509 packages and 14 document classes, each
  checked by a sample document of its own in `tests/packages/`, plus a
  glossary of about 630 more commands from CTAN packages that have no folder
  of their own. An unknown package produces a warning, not a failed build.
- **Fast.** On a release build, a one-page article takes a few milliseconds,
  and the 11-page sample paper in `build/main.mtex`, two passes included,
  takes under 30 ms.
- **Self-contained.** Packages and English hyphenation are compiled into the
  binary. Fonts (New Computer Modern, STIX Two, Fira Math, TeX Gyre and
  others) and hyphenation patterns for 79 languages and variants ship in
  `assets/`.
- **Embeddable.** The same engine is available as a C++ library, a C library
  that any language with a foreign-function interface can bind, and a
  WebAssembly module. Programs can supply values, commands they implement,
  and files from memory, then get the PDF back as bytes -- a whole document,
  or a snippet: one formula, table or picture on a page cropped to it.
- **Safe by design.** A document cannot run shell commands (`\write18` does
  not exist), cannot write files, and never loads `.sty` or `.cls` code from
  disk. With `--offline` it cannot reach the network either.

## How it works

1. **One program reads the whole document.** The lexer reads the source
   into tokens, the expander runs its macros and the parser builds its
   structure. Nothing comes from a TeX distribution: each package and class
   is a folder of the engine's own LaTeX, compiled into the binary, and the
   commands of about 630 more packages come from a glossary that costs
   nothing until a document uses one.
2. **Typesetting is compiled code.** Paragraphs are broken into lines and
   lines into pages by the engine itself, and text is shaped by HarfBuzz in
   the fonts the engine carries, hyphenated by patterns for 79 languages and
   variants.
3. **Cross-references resolve in memory.** Where LaTeX writes an `.aux` file
   and needs another run, mLaTeX makes its second pass in memory, so
   references and tables of contents come out right in one run. A `.bib`
   file is read directly, with no BibTeX step.
4. **The PDF is written directly.** Each font is subset to the glyphs the
   document uses, hyperref's links and bookmarks are kept, and pdfx's
   PDF/A-2b is written when a document asks for it.
5. **A document cannot reach outside.** It cannot run a shell command, write
   a file or load package code from disk, and with `--offline` it makes no
   network requests. [SECURITY.md](SECURITY.md) has the details.

## Features

**Documents**
- 509 packages and 14 document classes, each checked by a sample document of
  its own; an unknown package or class is a warning, not a failed build.
- Mathematics, floats, and tables that break across pages with their text
  kept inside its cells.
- Cross-references, tables of contents and indexes, resolved in one run.
- hyperref's links and bookmarks, and PDF/A.

**Pictures**
- TikZ, pgfplots, tikz-cd, xy-pic and forest pictures.
- PNG, JPEG, WebP, EPS and SVG pictures; an EPS picture is drawn by running
  its PostScript.

**Slides**
- beamer slides: each slide of a frame, with its overlays, and beamer's
  themes.

**Bibliographies**
- BibTeX bibliographies in the standard, natbib and biblatex styles.
- `\bibliography` and `\addbibresource` read the `.bib` file directly.
- `mlatex refs.bib` typesets every entry, to check a bibliography before
  citing it.

**Languages**
- Hyphenation patterns for 79 languages and variants.
- Right-to-left text: Arabic and Hebrew paragraphs and tables, mirrored
  brackets and kashida justification.
- Chinese and Japanese broken between their characters, and each language's
  own digits and spacing.

**The command line**
- TeX's own options, so scripts written for pdfLaTeX keep working.
- `--watch` sets the document again every time it is saved, and `--open`
  opens the PDF in the system viewer.
- Errors as `file:line:column: message`, and `--time-statistics` for every
  stage of the engine.

**For programs**
- The engine as a C++ library, a C library and a WebAssembly module, with
  one interface under the same names.
- Values, commands and files handed in from memory, and the PDF handed back
  as bytes.
- Snippets: a formula, a table or a picture set on its own, on a page
  cropped to it.

## How it compares

|  | mLaTeX | pdfLaTeX | XeLaTeX | LuaLaTeX | Tectonic |
| --- | :---: | :---: | :---: | :---: | :---: |
| No TeX distribution to install | ✅ | ❌ | ❌ | ❌ | ✅ |
| Works offline from the first run | ✅ | ✅ | ✅ | ✅ | ❌ |
| Cross-references in one run, no auxiliary files | ✅ | ❌ | ❌ | ❌ | ✅ |
| OpenType fonts | ✅ | ❌ | ✅ | ✅ | ✅ |
| Any font installed on the system | ❌ | ❌ | ✅ | ✅ | ✅ |
| Reads packages from `.sty` files | ❌ | ✅ | ✅ | ✅ | ✅ |
| No shell commands from a document | ✅ | Restricted | Restricted | Restricted | Off by default |
| Usable as a library | ✅ C++, C | ❌ | ❌ | ❌ | ✅ Rust |
| Runs in a web page | ✅ | Third-party | Third-party | Third-party | ❌ |

mLaTeX carries its packages compiled in rather than reading `.sty` files:
509 of them, each checked by a document of its own, and the commands of
about 630 more in its glossary. It also has what none of these do together:
a session that a program hands values, commands and files from memory, and
snippets, a formula, table or picture set alone on a page cropped to it.

This table is the project's best reading of each engine's documentation and
may fall out of date. If something in it is wrong, please open an issue.

## Roadmap

**Next**
- Fonts loaded in the browser as a document asks for them, rather than all
  of `mlatex.data` before the first page
- Less memory: blocks committed as they fill, and a session that gives
  memory back between documents
- The `jit` target: an engine kept warm between runs, with what it built
  cached, that sets a document again as its files change

**Later**
- A `mlatex.Session` for Python, as JavaScript has
- `\printglossary` printing its list
- More classes with layouts of their own: Elsevier's `cas-sc` and `cas-dc`,
  `mdpi`, `siamart`, `apa7`, `exam`, `moderncv`, `tikzposter`, `ctexart`
  and others, and the NeurIPS, ICML, ACL and CVPR styles

Some things are left out by choice and will not come: `\write18`, reading a
`.sty` or `.cls` from disk, and a second run's `.aux`. See
[CHANGELOG.md](CHANGELOG.md) for what is left out and why.

## Platforms

| Platform | Status |
| --- | --- |
| Windows | Works, on x64 and ARM64. |
| macOS | Works, on Apple silicon and Intel. |
| Linux | Works, on x64 and ARM64. |
| Web and Node | Works, as a WebAssembly module. |
| Python | Works, through the C library and `ctypes`. |

Every release on the [Releases](https://github.com/modern-latex/mlatex/releases)
page carries packages for all of them:

| Platform   | Package                                                | Installs to                                         |
|------------|--------------------------------------------------------|-----------------------------------------------------|
| Windows    | `.msi` installer, `.zip`                               | `C:\Program Files\mLaTeX`                           |
| macOS      | `.pkg` installer                                       | `/Applications/mLaTeX`                              |
| macOS      | `.dmg` disk image, `.tar.gz`, `.zip`                   | wherever the `mLaTeX` folder is dragged or unpacked |
| Linux      | `.deb`, `.rpm`                                         | `/opt/mlatex`                                       |
| Linux      | `.tar.gz`, `.zip`                                      | wherever it is unpacked                             |
| Web        | `-wasm.zip`: `mlatex.js`, `mlatex.wasm`, `mlatex.data` | beside the page or script that loads it             |
| JavaScript | `.tgz`, the npm package `@modern-latex/mlatex`         | a project's `node_modules`, with `npm install`      |
| Python     | `.whl` for each platform and architecture              | a Python environment, with `pip install`            |

Each package is named for its platform and architecture, for example
`mlatex-0.1.0-windows-x64.msi` or `mlatex_0.1.0_arm64.deb`. The program is
`bin/mlatex` inside the installed folder. Add that `bin` folder to your `PATH`
to run it from anywhere. It is named `mlatex` so that it never collides with
the `latex` a TeX distribution installs. The JavaScript package and the
Python wheels are not on npm or PyPI yet: install them from the files
attached to a release.

### How releases are made

The Build workflow builds, tests and packages mLaTeX on every push to
`main`: Windows, macOS and Linux, each on x64 and ARM64, and then the
WebAssembly module. When it passes and `VERSION` names a version that has no
release yet, the Release workflow tags that commit and publishes what Build
packaged. `VERSION` holds the version on its first line and the release's
title on its second, and `releases/<version>.md` holds that release's notes.
To ship the next version, raise `VERSION` and add its notes.

Alphas and betas come before each version, named like `0.2.0-beta.2`, and
are published as pre-releases. Every release's notes say what it added and
fixed, and what doesn't work yet.

## Building from source

### Requirements

- CMake 3.25 or later and Ninja.
- A C++26 compiler with `#embed`: Clang 19 or later, or GCC 15 or later. On
  Windows, use the `clang-cl` that Visual Studio installs under
  `VC/Tools/Llvm`. The build selects it automatically if your IDE profile
  names MSVC (`cl`) or MinGW.
- [vcpkg](https://vcpkg.io) with HarfBuzz, libpng, libjpeg-turbo, libwebp,
  zlib and asmjit installed for your target triplet. The WebAssembly build
  doesn't need asmjit.
- [gperf](https://www.gnu.org/software/gperf/).
- Optional: libcurl on Linux and macOS for `\includegraphics` of `https://`
  sources (Windows uses WinHTTP); Doxygen for the API reference; WiX (version 3, or the `wix` .NET tool, version 4 or
  later) for an `.msi`.
  WiX 7 needs its EULA accepted once per machine, `wix eula accept wix7`,
  and the `WixToolset.UI.wixext` and `WixToolset.Util.wixext` extensions (`wix extension add --global ...`); see
  [WiX's maintenance fee](https://docs.firegiant.com/wix/osmf/).

```bash
vcpkg install harfbuzz libpng libjpeg-turbo libwebp zlib asmjit
```

### Build and test

```bash
cmake -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake
```

```bash
cmake --build cmake-build-release
```

```bash
ctest --test-dir cmake-build-release --output-on-failure
```

On Windows, the `debug`, `release` and `wasm` presets in
`CMakePresets.json` set all of this up (`cmake --preset release`). If you
leave out the toolchain file, the build looks for vcpkg in `VCPKG_ROOT` and
then in `C:/vcpkg`.

The build produces three targets: `latex` (the command-line program, built as `mlatex`), `core`
(the engine as a static library, which every other target links) and `ffi`
(the C library, `latex_ffi`). Every source file has a matching test under
`tests/`.

### Packaging

From a Release build tree:

```bash
cpack --config cmake-build-release/CPackConfig.cmake
```

This puts the packages listed under [Platforms](#platforms) for the
platform and architecture of the build into the `release/` folder at the
top of the project. To package another
architecture, run a separate build for it, for example `clang-cl` targeting
ARM64 with the `arm64-windows` triplet. On macOS,
`-DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"` with universal libraries
produces one disk image for both.

## Usage

```bash
mlatex paper
```

This compiles `paper.mtex` or, failing that, `paper.tex`, and writes
`paper.pdf` beside it. Options accept one or two dashes and are written as
words separated by dashes. TeX's own spellings are accepted too, so scripts
written for pdfLaTeX keep working.

```bash
mlatex --interaction=batch-mode --halt-on-error paper
```

```bash
mlatex --output-directory=out --job-name=final paper.tex
```

```bash
mlatex -I styles -I figures paper
```

```bash
mlatex --watch --open paper
```

```bash
mlatex --time paper
```

| Option                          | Meaning                                                              |
|---------------------------------|----------------------------------------------------------------------|
| `-o`, `--output-directory=DIR`  | Write the PDF into `DIR`                                             |
| `-j`, `--job-name=NAME`         | Name the PDF `NAME.pdf`                                              |
| `-n`, `--draft-mode`            | Check the document and write no PDF                                  |
| `--halt-on-error`               | Write no PDF if the document has an error                            |
| `-I`, `--include-directory=DIR` | Also look in `DIR` for inputs, packages, pictures and bibliographies |
| `--offline`                     | Make no network requests; for documents you did not write            |
| `-w`, `--watch`                 | Recompile every time the document is saved                           |
| `-O`, `--open`                  | Open the PDF in the system viewer when it is written                 |
| `-i`, `--interaction=MODE`      | `batch-mode` prints only errors                                      |
| `--file-line-error`             | Print errors as `file:line:column: message`                          |
| `-T`, `--time`                  | Print how long the run took                                          |
| `--time-statistics`             | Print every stage of the engine and its timing                       |

`mlatex --help` lists every option. The exit status is 0 for a clean
document, 1 for a document with errors (a PDF is still written unless
`--halt-on-error` is given), and 2 for a mistake on the command line.

### Bibliographies

`\bibliography{refs}` and biblatex's `\addbibresource{refs.bib}` read a
`.bib` file directly, so there is no separate BibTeX step. A `.bib` file can
also be imported with `\input{refs.bib}`. Running `mlatex refs.bib`
typesets every entry in the file, which is useful for checking a
bibliography before citing it.

### Writing packages

A package is a folder containing `main.mtex`, written in the same language
as a document. See [src/modules/packages.md](src/modules/packages.md).

## Embedding the engine

The command line is a thin layer over `latex::Session`, and every binding
exposes that same interface under the same names.

**C++**

```cpp
latex::Session session(latex::locate(program));
session.set("customer", "Acme Ltd.");
session.define({.name = "balance", .arity = 1, .handler = [&](auto arguments) {
    return ledger.balance(arguments[0]);
}});
session.provide("chart.png", png);

if (!session.typeset(document)) std::cerr << session.error;
send(session.pdf);
```

A whole document goes to `typeset`. A snippet -- a formula, a table, a
picture, with no preamble -- goes to `snippet`, which sets it as a
`standalone` document with amsmath and amssymb loaded and crops the page to
it, for an app or a web page to show among its own content:

```cpp
session.snippet(R"(\[ \int_0^1 x^2\,dx = \frac{1}{3} \])");
show(session.pdf);   // a page exactly the formula's size
```

`\documentclass{standalone}` does the same for a document written in full.

**C**, or any language that can call C (Python's ctypes, C#'s P/Invoke,
Rust, Go). The library exports a single function, `engine()`, declared in
`include/protocols/ffi.hpp`:

```c
const Latex* table = engine();
Session* session = table->compose(NULL);
table->set(session, "customer", "Acme Ltd.");

const unsigned char* pdf;
size_t size;
if (!table->typeset(session, source, strlen(source), &pdf, &size)) {
    fprintf(stderr, "%s", table->error(session));
}

const char* formula = "\\[ e^{i\\pi} + 1 = 0 \\]";
table->snippet(session, formula, strlen(formula), &pdf, &size);
table->dispose(session);
```

The library ships in every package: `latex_ffi.dll` on Windows,
`liblatex_ffi.dylib` on macOS and `liblatex_ffi.so` on Linux, with
`include/latex/ffi.hpp`.

**JavaScript**, through the WebAssembly module: `mlatex.js`, `mlatex.wasm` and
`mlatex.data` (the fonts), from the `mlatex-<version>-wasm.zip` of a release
or built with the `wasm` preset (see `include/render/wasm.hpp`). It runs in a
web page, a worker or Node:

```js
const engine = await mLatex();
const session = new engine.Session();
session.set("customer", "Acme Ltd.");
if (!session.typeset(source)) console.error(session.error());
const pdf = session.pdf();

session.snippet("\\[ e^{i\\pi} + 1 = 0 \\]");
const formula = session.pdf();   // a Uint8Array: hand it to PDF.js, or offer it as a download
session.delete();
```

## Documentation

The API reference is generated from the sources with Doxygen:

```bash
cmake --build cmake-build-release --target docs
```

It is written to `cmake-build-release/docs/html`. The reference and
[src/modules/packages.md](src/modules/packages.md) cover the engine's internals and
package authoring. [CHANGELOG.md](CHANGELOG.md) describes every feature in
detail.

## Project layout

| Path               | Contents                                                                                                                                                   |
|--------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `include/`, `src/` | The engine: `syntax` (lexer, expander, parser), `render` (layout, typography, graphics, PDF), `memory` (arenas, tables), `protocols` (HTTP, the C library) |
| `src/modules/`     | Packages and classes, one folder each, compiled into the binary                                                                                            |
| `src/jit/`         | The just-in-time target, being built                                                                                                                       |
| `assets/`          | Fonts, hyphenation patterns and the command glossary                                                                                                       |
| `build/`           | The sample paper, `main.mtex`                                                                                                                              |
| `tests/`           | One test per source file, at the same relative path, and in `tests/packages/` one sample document per package                                              |

## Security

Found a vulnerability? Please don't report it in a public issue. Report it
privately, with **Report a vulnerability** on the repository's **Security**
tab or by email to andromedeyz@hotmail.com, and read
[SECURITY.md](SECURITY.md) before disclosing anything publicly.

## Contributing

Contributions of every size are welcome. Start with
[CONTRIBUTING.md](CONTRIBUTING.md), which covers the
[Contributor License Agreement](CLA.md), and please read the
[Code of Conduct](CODE_OF_CONDUCT.md). Open an issue to report a bug or to
discuss a feature before starting on a large change. Pull requests should:

- build without warnings and pass `ctest`;
- add a test in the file that mirrors the source file they change;
- add an entry to [CHANGELOG.md](CHANGELOG.md).

Questions are welcome on [Discord](https://discord.gg/UUbPg5YtJF) or in an
issue. mLaTeX is maintained by Andres Hernandez
([\@ApaxPhoenix](https://github.com/ApaxPhoenix)); for questions about the
project or its direction, write to andromedeyz@hotmail.com.

## License

Copyright (C) 2026 Andres Hernandez.

mLaTeX is dual-licensed. It is free software under the
[GNU Affero General Public License v3.0](LICENSE), and is also available under
a commercial license for use the AGPL does not allow, such as in
closed-source products: see [LICENSING.md](LICENSING.md) and
[LICENSE-COMMERCIAL.md](LICENSE-COMMERCIAL.md). Contributions are accepted
under the [Contributor License Agreement](CLA.md) described in
[CONTRIBUTING.md](CONTRIBUTING.md).

The fonts, hyphenation patterns and libraries mLaTeX ships keep their own
licenses: see [THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md). The mLaTeX
name and logo are covered by [TRADEMARKS.md](TRADEMARKS.md).

## Acknowledgements

mLaTeX builds on [HarfBuzz](https://harfbuzz.github.io) for text shaping
and font subsetting, [FreeType](https://freetype.org),
[libpng](http://www.libpng.org), [libjpeg-turbo](https://libjpeg-turbo.org),
[libwebp](https://developers.google.com/speed/webp) and
[zlib](https://zlib.net). Its fonts include New Computer Modern, STIX Two,
Fira Math, Asana Math and the TeX Gyre math fonts, and its hyphenation
patterns come from the [hyph-utf8](https://www.hyphenation.org) project.
Above all, it owes its language to Donald Knuth's TeX and Leslie Lamport's
LaTeX.

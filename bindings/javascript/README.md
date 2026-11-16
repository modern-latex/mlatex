# @modern-latex/mlatex

A LaTeX typesetting engine, rewritten from the ground up in modern C++ and compiled to WebAssembly. It turns LaTeX into PDF in a web page, a worker or Node, with no TeX installation behind it and nothing sent anywhere.

```bash
npm install @modern-latex/mlatex
```

## Typeset a document

```js
import mLatex from "@modern-latex/mlatex";

const system = await mLatex();
const session = system.compose();

let pdf;
try {
    const made = session.typeset(String.raw`\documentclass{article}
\begin{document}
Hello, \LaTeX.
\end{document}`);
    if (!made) throw new Error(session.error());
    pdf = session.pdf();
} finally {
    session.dispose();
}
```

CommonJS works the same way: `const mLatex = require("@modern-latex/mlatex")`.

## Session API

Compose a session with `system.compose()`. It keeps values, commands, and files across documents.

| Operation | What it does |
| --- | --- |
| `set(name, value)`, `unset(name)` | A value the document reads with `\variable{name}`. |
| `define(name, arity, handler)`, `forget(name)` | A command your code answers: `handler` is called with each argument's text, and what it returns is set in the command's place. |
| `provide(name, content)`, `withdraw(name)` | A file under the name a document uses for it, as a `Uint8Array` or a string: `letterhead/main.mtex` for `\usepackage{letterhead}`, `chapter.tex` for `\input{chapter}`, `logo.png` for `\includegraphics{logo.png}`, `references.bib` for `\bibliography{references}`. |
| `typeset(document)` | Sets a document, and says whether it was set with nothing reported. |
| `snippet(text)` | Sets a piece of LaTeX alone, such as a formula or a table, on a page cropped to it. |
| `pdf()` | Returns the last PDF as a `Uint8Array` you can keep after disposing of the session. |
| `screen()` | Returns a copy of the pages for drawing to a canvas. Call `screen.dispose()` when you finish with it. |
| `error()` | What went wrong, one problem per line: `appendix.tex:3:5: error (macro): Undefined control sequence \foo`. |
| `dispose()` | Disposes of the session and its WebAssembly resources. |

```js
session.set("customer", "Acme Corporation");
session.define("balance", 1, (account) => ledger[account].toFixed(2));
session.provide("letterhead/main.mtex", String.raw`\newcommand{\letterhead}{\textbf{Acme}}`);
session.provide("logo.png", new Uint8Array(await logo.arrayBuffer()));
```

A package is a folder holding one file, `main.mtex`, written in the same language as a document; `.sty` and `.cls` files are not read. Classes are part of the engine.

## Where it runs

The package holds three files: `mlatex.js`, which loads the engine, `mlatex.wasm`, the engine itself, and `mlatex.data`, the fonts, packed into the engine's own file system.

- **Node** takes the package's own entry, which finds `mlatex.wasm` and `mlatex.data` beside it.
- **A worker or a page** loads `mlatex.js` with the other two files beside it, served from the same folder: `importScripts("/engine/mlatex.js")` in a classic worker, then `mLatex()`.
- **A bundler** that moves `mlatex.js` away from the other two says where they are:

```js
const system = await mLatex({ locateFile: (name) => `/engine/${name}` });
```

The engine starts no threads and makes no network requests: a picture from a URL is fetched by your code and handed in with `provide`.

## Links

- [Source and issues](https://github.com/modern-latex/mlatex)
- [Releases](https://github.com/modern-latex/mlatex/releases), with the command line for Windows, macOS and Linux

mLaTeX is licensed under the GNU Affero General Public License, version 3.

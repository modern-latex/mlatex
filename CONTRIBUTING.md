# Contributing to mLaTeX

Thank you for wanting to improve mLaTeX. Bug reports, documents that typeset
wrongly, and pull requests are all welcome.

## Before your first pull request: the CLA

mLaTeX is dual-licensed: under the GNU Affero General Public License v3.0 and
under commercial licenses (see [LICENSING.md](LICENSING.md)). To keep that
possible, every contribution of code, documentation or other material must
be made under the [mLaTeX Contributor License Agreement](CLA.md). You keep
the copyright in your work; the agreement lets the project license it under
both the AGPL and commercial terms.

To agree, include this sentence and your full legal name in the description
of your first pull request:

> I have read the mLaTeX Contributor License Agreement, version 1.0, and I
> agree to it for this and all my future contributions to mLaTeX.

Pull requests from contributors who have not agreed cannot be merged.

## Build and test

```bash
cmake --preset release
cmake --build --preset release
ctest --preset release
```

The presets in `CMakePresets.json` pick the compiler: LLVM's Clang on macOS
and Linux, `clang-cl` on Windows. Anything that belongs to one machine alone --
a compiler path, a toolchain -- goes in `CMakeUserPresets.json`, which is
never committed.

## Layout

| Component | Responsibility |
|-----------|----------------|
| `syntax` | The lexer, expander and parser. |
| `render` | Layout, typography, graphics and the PDF. |
| `memory` | Arenas and tables. |
| `protocols` | HTTP and the C library. |
| `jit` | The just-in-time target, being built. |
| `modules` | Packages and classes, one folder each, compiled into the binary. |

Each component has the same folder in `include/` and `src/`, and its tests the
same folder in `tests/`.

## Naming

One small vocabulary, the same in every project, in C++ and in every binding:

- **A value is named after its type.** A `State` is `state`, a `Session` is
  `session`, a `Canvas` is `canvas` -- never `ctx`, `s` or another word for it.
- **One word for each act.** Making or starting something is `compose`, never
  `create`, `init`, `begin` or `start`. Ending it and giving back what it holds
  is `dispose`, never `release`, `free`, `clear` or `destroy`.
- **What sort of thing a value is, is its `type`**, of an enum `Type` -- never
  `kind` or `category`.
- **One-word names.** Types are capitalised (`Storage`), everything else is
  lowercase (`prototype`, `source`). A name that needs two words usually
  belongs to a type of its own: `Storage::append`, not `append_storage`.

Names a standard, a file format or a third-party library fixes keep that
library's spelling.

In mLaTeX: `Session`, `Lexer`, `session`, `token`, `document`.

## Comments

Document what a header declares with `///` comments, as Doxygen reads them.
Explain what the code cannot say -- why it is this way, what it costs, what
it must never do -- not what it does. A comment that has drifted from its code
is worse than none.

## Verification

Every source file has a matching test under `tests/`, and every package a
sample document in `tests/packages/`. Pull requests build without warnings,
pass `ctest`, and add an entry to [CHANGELOG.md](CHANGELOG.md).

## Third-party material

Do not copy code, fonts, patterns or other material written by others into
a pull request unless you say so in it, with its source and license. In
particular:

- Code from LaTeX packages, TeX Live or other projects under the LPPL, GPL or
  similar licenses cannot be merged into mLaTeX's own source; reimplement
  the behavior instead.
- A new font or hyphenation pattern file must come unmodified from its
  upstream project, under a license that allows redistribution, and must be
  added, with its copyright and license, to `assets/fonts/LICENSES.md` or
  `assets/hyphens/LICENSES.md`.
- A new library dependency must be under a permissive license (MIT, BSD,
  Apache 2.0, zlib or similar) and must be added to
  [THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md).

## Commits and releases

A commit says what changed, in the past tense, as one sentence: "Numbered the
releases as alphas and betas". A release is `VERSION` raised on `main`, with
its notes in `releases/<version>.md` and its entry in
[CHANGELOG.md](CHANGELOG.md); the release workflow does the rest once Build
passes.

## Conduct and security

Everyone taking part is expected to follow the
[Code of Conduct](CODE_OF_CONDUCT.md). Report security problems privately,
as [SECURITY.md](SECURITY.md) describes, not in public issues.

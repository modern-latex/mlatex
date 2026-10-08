# Licensing

mLaTeX is **dual-licensed**. Copyright (C) 2026 Andres Hernandez.

You may use mLaTeX under **either** of these licenses, at your choice:

1. **The GNU Affero General Public License, version 3 only** (AGPL-3.0-only),
   whose full text is in [LICENSE](LICENSE). This is the open-source license
   every copy of mLaTeX, its source and its published packages (GitHub
   releases, npm, PyPI) carries. It lets anyone use, study, change and share
   mLaTeX for any purpose, including commercially, provided that whoever
   distributes mLaTeX, or a work based on it, or lets users interact with it
   over a network, makes the complete corresponding source code of that work
   available under the same license.

2. **A commercial license** from the copyright holder, for those who cannot
   or do not wish to meet the AGPL's conditions, for example to ship mLaTeX
   inside closed-source software or offer it as part of a hosted service
   without publishing their own source. See
   [LICENSE-COMMERCIAL.md](LICENSE-COMMERCIAL.md).

SPDX: `AGPL-3.0-only OR LicenseRef-mLaTeX-Commercial`

## Who holds the rights

The copyright in mLaTeX's own code, documentation, modules (the `.mtex`
files under `src/modules`) and `assets/glossary.mtex` and
`assets/unicodes.gperf` is held by Andres Hernandez, the project's author
and maintainer, who alone may grant commercial licenses for it. These rights
may be assigned to a company formed to steward mLaTeX (such as one named
mLaTeX), which would then grant commercial licenses in the copyright
holder's place; the AGPL license already granted on any published version is
not affected by such an assignment.

To keep dual licensing possible, every outside contribution is accepted only
under the [Contributor License Agreement](CLA.md); see
[CONTRIBUTING.md](CONTRIBUTING.md).

## What neither license covers

Third-party material that mLaTeX includes or links to keeps its own license,
and the commercial license grants no rights in it:

- the libraries listed in [THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md)
  (HarfBuzz, FreeType, libpng, libjpeg-turbo, libwebp, zlib and others);
- the fonts in `assets/fonts`, listed in
  [assets/fonts/LICENSES.md](assets/fonts/LICENSES.md);
- the hyphenation patterns in `assets/hyphens`, listed in
  [assets/hyphens/LICENSES.md](assets/hyphens/LICENSES.md).

All of them are under licenses that allow redistribution, but a few fonts
and pattern files are under copyleft licenses (GPL or LGPL), and one
pattern file states no license. Those files are named in the two lists
above, together with how a commercial distribution can leave them out.

## Your documents

The documents you write and the PDFs mLaTeX produces from them are yours.
Neither license claims any rights in them, and the AGPL's conditions do not
reach a document because mLaTeX typeset it. Fonts embedded in a PDF remain
under their own licenses, all of which allow that embedding.

## Name and logo

The licenses above cover the software, not the mLaTeX name or logo; see
[TRADEMARKS.md](TRADEMARKS.md).

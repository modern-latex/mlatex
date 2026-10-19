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

## Conduct and security

Everyone taking part is expected to follow the
[Code of Conduct](CODE_OF_CONDUCT.md). Report security problems privately,
as [SECURITY.md](SECURITY.md) describes, not in public issues.

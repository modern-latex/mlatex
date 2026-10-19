# Font licenses

mLaTeX ships the fonts in this folder unmodified, as separate files that the
engine reads at run time (or, in the WebAssembly build, packs into
`latex.data`). None of them is covered by mLaTeX's own license: each keeps
the license its authors gave it, listed below, and its full text is in this
folder. Embedding one of these fonts (or a subset of it) in a PDF that
mLaTeX produces is permitted by every license here.

| Files | Copyright | License | Text |
|-------|-----------|---------|------|
| `text/lm*.otf` (Latin Modern) | B. Jackowski, J. M. Nowacki and the Polish TeX Users Group GUST, on behalf of the TeX users groups | GUST Font License (LPPL 1.3c or later) | `GUST-FONT-LICENSE.txt`, `LPPL-1.3c.txt` |
| `text/NewCM*`, `expression/NewCM*` (New Computer Modern), except the four rows below | (C) 2019-2026 Antonis Tsolomitis | GUST Font License (LPPL 1.3c or later) | `NewComputerModern-License.txt`, `GUST-FONT-LICENSE.txt`, `LPPL-1.3c.txt` |
| `text/NewCM10-Regular.otf` | (C) 2019-2026 Antonis Tsolomitis | GPL 3 or later, with the Font Exception and Distribution Exception | `NewComputerModern-License.txt` |
| `text/NewCMUncial*.otf` | (C) 2021 Antonis Tsolomitis | GPL 3 or later, with the Font Exception and Distribution Exception | `NewComputerModern-License.txt` |
| `text/NewCM*Devanagari-*.otf` | (C) 2023-2026 Antonis Tsolomitis and Niranjan | GPL 3 or later, with the Font Exception and Distribution Exception | `NewComputerModern-License.txt` |
| `text/STIXTwoText-*.otf`, `expression/STIXTwoMath-Regular.otf` | Copyright 2001-2021 The STIX Fonts Project Authors (https://github.com/stipub/stixfonts). STIX Fonts and STIX Two are trademarks of The Institute of Electrical and Electronics Engineers, Inc. | SIL Open Font License 1.1 | `OFL-1.1.txt` |
| `text/NotoNaskhArabic-*.ttf` | Copyright 2014 Google Inc. Noto is a trademark of Google Inc. | SIL Open Font License 1.1 | `NotoNaskhArabic-OFL.txt` |
| `expression/Asana-Math.otf` | Copyright (c) 2007-2025 Apostolos Syropoulos, with Reserved Font Name Asana Math; Copyright (c) 2000 Young Ryu, with Reserved Font Name pxfonts; Copyright (c) 1997, 1999 Claudio Beccari, with Reserved Font Name gsmn1000 | SIL Open Font License 1.1 | `OFL-1.1.txt` |
| `expression/FiraMath-Regular.otf` | Copyright (C) 2018-2020 Xiangdong Zeng. Fira Sans is a trademark of The Mozilla Corporation. | SIL Open Font License 1.1 | `OFL-1.1.txt` |
| `expression/texgyrebonum-math.otf`, `texgyrepagella-math.otf`, `texgyreschola-math.otf`, `texgyretermes-math.otf` (TeX Gyre Math) | Copyright 2012-2014 B. Jackowski, P. Strzelczyk and P. Pianowski, on behalf of the TeX users groups | GUST Font License (LPPL 1.3c or later) | `GUST-FONT-LICENSE.txt`, `LPPL-1.3c.txt` |
| `expression/texgyredejavu-math.otf` (TeX Gyre DejaVu Math) | Copyright (c) 2003 Bitstream, Inc.; DejaVu changes and math extensions are in the public domain; TeX Gyre additions by the GUST e-foundry | GUST Font License, and the Bitstream Vera / DejaVu license for the glyphs it derives from | `GUST-FONT-LICENSE.txt`, `DejaVu-License.txt` |

The upstream packages are on CTAN: `lm`, `newcomputermodern`, `stix2-otf`,
`asana-math`, `firamath` and `tex-gyre-math`; Noto Naskh Arabic is from
https://github.com/notofonts/arabic. Their sources are available there.

## Notes for redistributors

- These fonts are distributed alongside mLaTeX as an aggregate; their
  licenses neither extend to mLaTeX's code nor are changed by mLaTeX's
  license, including by a commercial license for mLaTeX (see `LICENSING.md`
  at the root of the source tree).
- The GPL-licensed New Computer Modern files (the rows marked GPL above)
  may be redistributed with proprietary software as separate files, but
  must keep this license, and recipients must be able to obtain their
  source from CTAN. A distribution that prefers to carry no GPL-licensed
  material can leave them out: `NewCM10-Book.otf` and Latin Modern are
  GUST-licensed alternatives.
- The OFL and GUST licenses ask that a modified font be renamed. mLaTeX
  ships every font unmodified.

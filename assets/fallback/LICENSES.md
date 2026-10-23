# Font licenses

The faces in this folder are lent to a web page, not packed into
`mlatex.data`: a browser lends a page none of the system's faces, so a page
fetches one of these only when a document lacks characters it draws, as
`screen.missing()` names them and `fonts.json` says, and hands it over with
`session.font`. mLaTeX ships them unmodified, as separate files; none is
covered by mLaTeX's own license. Embedding one of them (or a subset of it)
in a PDF that mLaTeX produces is permitted by their license.

`NotoSerifCJK-Regular.otf` is `NotoSerifCJKsc-Regular.otf`, renamed so that
mLaTeX finds it by the name it looks for, and `NotoEmoji-Regular.ttf` is
`NotoEmoji[wght].ttf`, renamed the same way.

| Files | Copyright | License | Text |
|-------|-----------|---------|------|
| `NotoSerifCJK-Regular.otf` (Noto Serif CJK) | Copyright 2017-2022 Adobe (http://www.adobe.com/), with Reserved Font Name 'Source'. Noto is a trademark of Google Inc. | SIL Open Font License 1.1 | `OFL-1.1.txt` |
| `NotoEmoji-Regular.ttf` | Copyright 2013 Google LLC | SIL Open Font License 1.1 | `OFL-1.1.txt` |
| `NotoSans*-Regular.ttf`, `NotoSerif*-Regular.ttf` (the other scripts and the symbols) | Copyright 2012-2022 The Noto Project Authors (https://github.com/notofonts) | SIL Open Font License 1.1 | `OFL-1.1.txt` |

They are from https://github.com/notofonts/noto-cjk,
https://github.com/notofonts/notofonts.github.io and
https://github.com/google/fonts. `fonts.json` is written from them by
`bindings/javascript/coverage.js`.

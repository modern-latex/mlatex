# Hyphenation pattern licenses

The files in this folder come unmodified from the
[hyph-utf8](https://www.hyphenation.org) project
(https://github.com/hyphenation/tex-hyphen), in its plain-text form
(`hyph-*.pat.txt` for the patterns, `hyph-*.hyp.txt` for the exceptions).
mLaTeX compiles `hyph-en-us.pat.txt` into the engine and reads every other
file here at run time. None of them is covered by mLaTeX's own license: each
keeps the license its authors gave it.

The plain-text files carry no header, so each one's title, copyright and
license, as its upstream `hyph-*.tex` source states them, are reproduced
below. Full texts of the licenses the headers name only by reference are in
this folder: `LICENSE-GPL-2.0.txt`, `LICENSE-GPL-3.0.txt`,
`LICENSE-LGPL-2.1.txt`, `LICENSE-LGPL-3.0.txt`, `LICENSE-LPPL-1.3c.txt` and
`LICENSE-MPL-1.1.txt`. Where a file is offered under several licenses ("any
of these licences"), mLaTeX uses it under the most permissive of them.

## Summary

Permissive (MIT, BSD, public domain, or a notice-only permission, alone or as
one choice of several): every language not listed below.

| Files | Terms | Note |
|-------|-------|------|
| `hyph-ca`, `hyph-eo`, `hyph-hr`, `hyph-hsb`, `hyph-ia`, `hyph-is`, `hyph-kmr`, `hyph-ru`, `hyph-sh-cyrl`, `hyph-sh-latn`, `hyph-sv`, `hyph-th`, `hyph-tr` | LaTeX Project Public License | Free to redistribute unmodified, including commercially. |
| `hyph-hu` | MPL 1.1, GPL 2 or LGPL 2.1, at the recipient's choice | Used under the MPL 1.1, which is file-level. |
| `hyph-hy` | LGPL | Weak copyleft on these data files themselves. |
| `hyph-lv` | LGPL 2.1 or GPL 2 or later | Weak copyleft on these data files themselves. |
| `hyph-cs` | GPL 2 or later | Copyleft. |
| `hyph-id` | GPL 2 | Copyleft. |
| `hyph-mk` | GPL | Copyleft. |
| `hyph-sr-cyrl` | GPL | Copyleft. |
| `hyph-ro` | None stated upstream | Distributed by hyph-utf8 and TeX Live with no license given. |

These pattern files are data that the engine reads at run time; they are
distributed alongside mLaTeX as an aggregate and their licenses do not extend
to mLaTeX's code. A distribution of mLaTeX under a commercial license that
should carry no copyleft or unlicensed material can leave out the files in
the last seven rows, or replace them with patterns under other terms,
after checking how the engine behaves without them.

## Per-file notices

## hyph-af

Files: `hyph-af.pat.txt`, `hyph-af.hyp.txt`

```
title: Hyphenation patterns for Afrikaans
copyright: Copyright (C) 2013 Tilla Fick and Chris Swanepoel
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    text: |-
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in
        all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
```

## hyph-as

Files: `hyph-as.pat.txt`

```
title: Hyphenation patterns for Assamese
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-be

Files: `hyph-be.pat.txt`

```
title: Hyphenation patterns for Belarusian
copyright: Copyright (C) 2016 Maksim Salau
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-bg

Files: `hyph-bg.pat.txt`

```
copyright: Copyright (C) 2000, 2004, 2017 Anton Zinoviev
title: Hyphenation patterns for Bulgarian
notice: >
    This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
    The Bulgarian patterns used to come from another file,
    by Georgi Boshnakov, named bghyphen.tex
licence:
    text: > # Seems equivalent to 3-clause BSD
        This software may be used, modified, copied, distributed, and sold,
        both in source and binary form provided that the above copyright
        notice and these terms are retained. The name of the author may not
        be used to endorse or promote products derived from this software
        without prior permission.  THIS SOFTWARE IS PROVIDES "AS IS" AND
        ANY EXPRESS OR IMPLIED WARRANTIES ARE DISCLAIMED.  IN NO EVENT
        SHALL THE AUTHOR BE LIABLE FOR ANY DAMAGES ARISING IN ANY WAY OUT
        OF THE USE OF THIS SOFTWARE.
```

## hyph-ca

Files: `hyph-ca.pat.txt`, `hyph-ca.hyp.txt`

```
title: Hyphenation patterns for Catalan
copyright: Copyright (C) December 1991-January 1995, July 2003 Gonçal Badenes
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1
    or_later: true
    url: https://latex-project.org/lppl/
```

## hyph-cop

Files: `hyph-cop.pat.txt`

```
title: Hyphenation patterns for Coptic
copyright: Copyright (C) 2004—2010 Claudio Beccari
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-cs

Files: `hyph-cs.pat.txt`, `hyph-cs.hyp.txt`

```
title: Hyphenation patterns for Czech
copyright: Copyright (C) 1995 Pavel Ševeček
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: GPL
    version: 2
    or_later: true
    url: http://www.gnu.org/licenses/gpl.html
```

## hyph-cu

Files: `hyph-cu.pat.txt`, `hyph-cu.hyp.txt`

```
title: Hyphenation patterns for Church Slavonic
copyright: Copyright (C) 2016 Aleksandr Andreev, Mike Kroutikov
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person obtaining
        a copy of this software and associated documentation files (the
        "Software"), to deal in the Software without restriction, including
        without limitation the rights to use, copy, modify, merge, publish,
        distribute, sublicense, and/or sell copies of the Software, and to
        permit persons to whom the Software is furnished to do so, subject to
        the following conditions:

        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
        MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
        BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
        ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
        CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
```

## hyph-cy

Files: `hyph-cy.pat.txt`

```
title: Hyphenation patterns for Welsh
copyright: Copyright (C) 1996 Yannis Haralambous
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of these licences:
    -
        name: LPPL
        status: maintained
        maintainer: Yannis Haralambous
        version: 1.0
        or_later: true
        url: http://www.latex-project.org/lppl/lppl-1-0.html
    -
        name: MIT
        url: https://opensource.org/licences/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-da

Files: `hyph-da.pat.txt`

```
title: Hyphenation patterns for Danish
copyright: Copyright (C) 1994 Frank Jensen
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of these licences:
    -
        name: LPPL
        version: 1.3
        or_later: true
        url: http://www.latex-project.org/lppl/lppl-1-3.html
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-de-1901

Files: `hyph-de-1901.pat.txt`

```
title: German Hyphenation Patterns (Traditional Orthography)

notice: TeX-Trennmuster für die traditionelle deutsche Rechtschreibung

copyright: Copyright (c) 2013-2024
           Stephan Hennig, Werner Lemberg, Günter Milde,
           Sander van Geloven, Georg Pfeiffer, Gisbert W. Selke,
           Tobias Wendorf, Keno Wehr

licence:
    name: MIT
    url:  https://opensource.org/licenses/mit-license.php
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-de-1996

Files: `hyph-de-1996.pat.txt`

```
title: German Hyphenation Patterns (Reformed Orthography, 2006)

notice: TeX-Trennmuster für die reformierte (2006) deutsche Rechtschreibung

copyright: Copyright (c) 2013-2024
           Stephan Hennig, Werner Lemberg, Günter Milde,
           Sander van Geloven, Georg Pfeiffer, Gisbert W. Selke,
           Tobias Wendorf, Keno Wehr

licence:
    name: MIT
    url:  https://opensource.org/licenses/mit-license.php
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-de-ch-1901

Files: `hyph-de-ch-1901.pat.txt`

```
title: Swiss-German Hyphenation Patterns (Traditional Orthography)

notice: TeX-Trennmuster für die traditionelle deutsch-schweizerische Rechtschreibung

copyright: Copyright (c) 2013-2024
           Stephan Hennig, Werner Lemberg, Günter Milde,
           Sander van Geloven, Georg Pfeiffer, Gisbert W. Selke,
           Tobias Wendorf, Keno Wehr

licence:
    name: MIT
    url:  https://opensource.org/licenses/mit-license.php
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-el-monoton

Files: `hyph-el-monoton.pat.txt`

```
title: Hyphenation patterns for Modern Greek, monotonic
copyright: Copyright (C) 2008-2011 Dimitrios Filippou
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: LPPL
        url: https://latex-project.org/lppl/
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
```

## hyph-el-polyton

Files: `hyph-el-polyton.pat.txt`

```
title: Hyphenation patterns for Modern Greek, polytonic
copyright: Copyright (C) 2008-2011 Dimitrios Filippou
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: LPPL
        url: https://latex-project.org/lppl/
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
```

## hyph-en-gb

Files: `hyph-en-gb.pat.txt`, `hyph-en-gb.hyp.txt`

```
title: Hyphenation patterns for British English
copyright: Copyright (C) 1992, 1996, 2005, 2016 Dominik Wujastyk, Graham Toal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-en-us

Files: `hyph-en-us.pat.txt`, `hyph-en-us.hyp.txt`

```
title: Hyphenation patterns for American English
copyright: Copyright (C) 1990, 2004, 2005 Gerard D.C. Kuiken
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    text: >
        Copying and distribution of this file, with or without modification,
        are permitted in any medium without royalty provided the copyright
        notice and this notice are preserved.
```

## hyph-eo

Files: `hyph-eo.pat.txt`

```
title: Hyphenation patterns for Esperanto
copyright: Copyright (C) 1999 Sergei B. Pokrovsky (Sergio Pokrovskij)
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1
    or_later: true
    url: https://latex-project.org/lppl/
```

## hyph-es

Files: `hyph-es.pat.txt`

```
copyright: Copyright (C) 1993, 1997 Javier Bezos, 2001-2019 Javier Bezos, CervanTeX
title: Hyphenation patterns for Spanish
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT/X11
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in
        all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
```

## hyph-et

Files: `hyph-et.pat.txt`

```
title: Hyphenation patterns for Estonian
copyright: Copyright (C) 2004-2015 Enn Saar
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is dual-licensed under both these licences, at your discretion:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LPPL
        version: 1.3
        or_later: true
        status: author-maintained
        url: http://www.latex-project.org/lppl.txt
```

## hyph-eu

Files: `hyph-eu.pat.txt`

```
copyright: Copyright (C) 1997, 2008 Juan M. Aguirregabiria
title: Hyphenation patterns for Basque
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information on the package,
    and http://tp.lc.ehu.es/jma/basque.html for details on Basque hyphenation.
licence:
    text: >
        Permission is hereby granted, free of charge, to any person obtaining
        a copy of this file and any associated documentation
        (the "Data Files") to deal in the Data Files
        without restriction, including without limitation the rights to use,
        copy, modify, merge, publish, distribute, and/or sell copies of
        the Data Files, and to permit persons to whom the Data Files
        are furnished to do so, provided that
        (a) this copyright and permission notice appear with all copies
        of the Data Files,
        (b) this copyright and permission notice appear in associated
        documentation, and
        (c) there is clear notice in each modified Data File
        as well as in the documentation associated with the Data File(s)
        that the data has been modified.

        THE DATA FILES ARE PROVIDED "AS IS", WITHOUT WARRANTY OF
        ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
        WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT OF THIRD PARTY RIGHTS.
        IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS
        NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL
        DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
        DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
        TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
        PERFORMANCE OF THE DATA FILES.

        Except as contained in this notice, the name of a copyright holder
        shall not be used in advertising or otherwise to promote the sale,
        use or other dealings in these Data Files without prior
        written authorization of the copyright holder.
```

## hyph-fi-x-school

Files: `hyph-fi-x-school.pat.txt`

```
title: Hyphenation patterns for Finnish according to the method taught in schools
copyright: Copyright (C) 2020 Teemu Likonen, Arthur Rosendahl
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
```

## hyph-fi

Files: `hyph-fi.pat.txt`

```
title: Hyphenation patterns for Finnish
copyright: Copyright (C) 1986, 1988, 1989 Kauko Saarinen
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - text: Patterns may be freely distributed
```

## hyph-fr

Files: `hyph-fr.pat.txt`

```
title: Hyphenation patterns for French
copyright: Copyright (C) 1994-2002 Daniel Flipo, Bernard Gaulle, 2016 Arthur Reutenauer
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person obtaining
        a copy of this software and associated documentation files (the
        "Software"), to deal in the Software without restriction, including
        without limitation the rights to use, copy, modify, merge, publish,
        distribute, sublicense, and/or sell copies of the Software, and to
        permit persons to whom the Software is furnished to do so, subject to
        the following conditions:

        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
        MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
        BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
        ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
        CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
```

## hyph-fur

Files: `hyph-fur.pat.txt`

```
title: Hyphenation patterns for Friulan
copyright: Copyright (C) 2012 Claudio Beccari
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences, at your option:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LPPL
        version: 1.3
        or_later: true
        url: http://www.latex-project.org/lppl.txt
        status: maintained
        maintainer: Claudio Beccari
```

## hyph-ga

Files: `hyph-ga.pat.txt`, `hyph-ga.hyp.txt`

```
title: Hyphenation patterns for Irish
copyright: Copyright (C) 2004-2015 Kevin P. Scannell
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information on the package,
    and http://borel.slu.edu/fleiscin/index.html for details on Irish hyphenation.
licence:
    - This file available under any of these licences:
    -
        name: GPL
        version: 2
        or_later: true
        url: http://www.gnu.org/licenses/gpl-2.0.html
        text: >
            This program is free software; you can redistribute it and/or
            modify it under the terms of the GNU General Public License
            as published by the Free Software Foundation; either version 2
            of the License, or (at your option) any later version.
           
            This program is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of
            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
            GNU General Public License for more details.
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-gl

Files: `hyph-gl.pat.txt`

```
title: Hyphenation patterns for Galician
copyright: Copyright (C) 2006, 2007, 2008, 2010 Javier A. Múgica
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: Unlicence
    url: https://unlicense.org/
```

## hyph-grc

Files: `hyph-grc.pat.txt`

```
title: Hyphenation patterns for Ancient Greek
copyright: Copyright (C) 2008-2016 Dimitrios Filippou
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: LPPL
        url: http://www.latex-project.org/lppl/
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
```

## hyph-gu

Files: `hyph-gu.pat.txt`

```
title: Hyphenation patterns for Gujarati
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-hr

Files: `hyph-hr.pat.txt`

```
title: Hyphenation patterns for Croatian
copyright: Copyright (C) 1994, 1996, 2011, 2015 Igor Marinović
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of these licences:
    -
        name: LPPL
        version: 1
        or_later: true
        url: http://www.latex-project.org/lppl/lppl-1-0.html
    -
        text: >
            Permission is hereby granted, free of charge, to any person obtaining
            a copy of this file and any associated documentation
            (the "Data Files") to deal in the Data Files
            without restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, and/or sell copies of
            the Data Files, and to permit persons to whom the Data Files
            are furnished to do so, provided that
            (a) this copyright and permission notice appear with all copies 
            of the Data Files,
            (b) this copyright and permission notice appear in associated 
            documentation, and
            (c) there is clear notice in each modified Data File
            as well as in the documentation associated with the Data File(s)
            that the data has been modified.
            
            THE DATA FILES ARE PROVIDED "AS IS", WITHOUT WARRANTY OF
            ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
            WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT OF THIRD PARTY RIGHTS.
            IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS
            NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL
            DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
            DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
            TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
            PERFORMANCE OF THE DATA FILES.
            
            Except as contained in this notice, the name of a copyright holder
            shall not be used in advertising or otherwise to promote the sale,
            use or other dealings in these Data Files without prior
            written authorization of the copyright holder.
```

## hyph-hsb

Files: `hyph-hsb.pat.txt`, `hyph-hsb.hyp.txt`

```
title: Hyphenation patterns for Upper Sorbian
copyright: Copyright (C) 1997 Eduard Werner
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.3
    or_later: true
    url: http://www.latex-project.org/lppl.txt
```

## hyph-hu

Files: `hyph-hu.pat.txt`

```
title: Hyphenation patterns for Hungarian
copyright: Copyright (C) 2003 Bence Nagy
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of these licences, at your option:
    -
        name: MPL
        version: 1.1
        initial_developer: Bence Nagy
        contributors:
            - Bence Nagy
        url: https://www.mozilla.org/en-US/MPL/1.1/
    -
        name: GPL
        version: 2.0
        url: http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
    -
        name: LGPL
        version: 2.1
        url: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
```

## hyph-hy

Files: `hyph-hy.pat.txt`

```
title: Hyphenation patterns for Armenian
copyright: Copyright (C) 2010 Sahak Petrosyan
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LGPL
    url: https://www.gnu.org/licenses/lgpl-3.0.en.html
```

## hyph-ia

Files: `hyph-ia.pat.txt`, `hyph-ia.hyp.txt`

```
title: Hyphenation patterns for Interlingua
copyright: Copyright (C) 1989-2005 Peter Kleiweg
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.3
    status: maintained
    maintainer: Peter Kleiweg
    url: https://latex-project.org/lppl/
```

## hyph-id

Files: `hyph-id.pat.txt`, `hyph-id.hyp.txt`

```
title: Hyphenation patterns for Bahasa Indonesia
copyright: Copyright (C) 1996, 1997 Jörg Knappen, Terry Mart
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: GPL
    version: 2
    url: http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
```

## hyph-is

Files: `hyph-is.pat.txt`

```
title: Hyphenation patterns for Icelandic
copyright: Copyright (C) 1988, 2004 Jörgen Pind
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.2
    or_later: true
    url: http://www.latex-project.org/lppl.txt
```

## hyph-it

Files: `hyph-it.pat.txt`

```
title: Hyphenation patterns for Italian
copyright: Copyright (C) 2008-2011 Claudio Beccari
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: LPPL
        version: 1.3
        or_later: true
        url: http://www.latex-project.org/lppl.txt
        status: maintained
        maintainer: Claudio Beccari, e-mail claudio dot beccari at gmail dot com
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-ka

Files: `hyph-ka.pat.txt`

```
title: Hyphenation patterns for Georgian
copyright: Copyright (C) 2013 Levan Shoshiashvili
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
```

## hyph-kk

Files: `hyph-kk.pat.txt`

```
title: Hyphenation patterns for Kazakh (hyph-kk.tex)
copyright: Copyright (C) 2010 Mojca Miklavec, 2025 Robert Ermers, 2026 Arthur Rosendahl
notice: This file is part of the hyph-utf8 package.
    See https://www.hyphenation.org/tex for more information
licence:
    name: Public domain
```

## hyph-kmr

Files: `hyph-kmr.pat.txt`

```
title: Hyphenation patterns for Kurmanji (Northern Kurdish)
    – as spoken in Turkey and by the Kurdish diaspora in Europe
copyright: Copyright (C) 2009 Jörg Knappen, Medeni Shemdê
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.3
    status: maintained
    maintainer: Jörg Knappen
    url: https://latex-project.org/lppl/lppl-1-3.html
```

## hyph-kn

Files: `hyph-kn.pat.txt`

```
title: Hyphenation patterns for Kannada
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-la-x-classic

Files: `hyph-la-x-classic.pat.txt`

```
title: Hyphenation patterns for classical Latin
copyright: Copyright (C) 2019 Keno Wehr
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
    These patterns are also suitable for medieval and modern Latin if German
    or Slavic pronunciation is used.
    See https://github.com/gregorio-project/hyphen-la/tree/master/doc for
    documentation.
licence:
    name: MIT
    url:  http://opensource.org/licenses/MIT
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the "Software"), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-la-x-liturgic

Files: `hyph-la-x-liturgic.pat.txt`

```
copyright: Copyright (C) 2016-2019 Claudio Beccari, Elie Roux
title: Hyphenation patterns for liturgical Latin
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
  -
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person obtaining
        a copy of this software and associated documentation files (the
        "Software"), to deal in the Software without restriction, including
        without limitation the rights to use, copy, modify, merge, publish,
        distribute, sublicense, and/or sell copies of the Software, and to
        permit persons to whom the Software is furnished to do so, subject to
        the following conditions:

        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
        MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
        BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
        ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
        CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
```

## hyph-la

Files: `hyph-la.pat.txt`

```
title: Hyphenation patterns for modern and medieval Latin
copyright: Copyright (C) 1999-2016 Claudio Beccari
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the “Software”), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LPPL
        version: 1
        or_later: true
        url: https://latex-project.org/lppl/
```

## hyph-lt

Files: `hyph-lt.pat.txt`

```
title: Hyphenation patterns for Lithuanian
copyright: Copyright (C) 1992 Sigitas Tolušis, Yannis Haralambous
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person
        obtaining a copy of this software and associated documentation
        files (the "Software"), to deal in the Software without
        restriction, including without limitation the rights to use,
        copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the
        Software is furnished to do so, subject to the following
        conditions:

        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
        OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
        HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
        WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
        FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
        OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-lv

Files: `hyph-lv.pat.txt`

```
title: Hyphenation patterns for Latvian
copyright: Copyright (C) 2004-2005 Janis Vilims
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences, at your option:
    -
        name: LGPL
        version: 2.1
        url: http://www.gnu.org/copyleft/lesser.txt
    -
        name: GPL
        version: 2
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-mk

Files: `hyph-mk.pat.txt`

```
title: Hyphenation patterns for Macedonian
copyright: Copyright (C) 2006 Vasil Taneski
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - name: GPL
```

## hyph-ml

Files: `hyph-ml.pat.txt`

```
title: Hyphenation patterns for Malayalam
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-mn-cyrl

Files: `hyph-mn-cyrl.pat.txt`

```
title: Hyphenation patterns for Mongolian, Cyrillic script
copyright: Copyright (C) 2007-2015 by Dorjgotov Batmunkh
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licenses:
    -
        name: LPPL
        version: 1.3
        or_later: true
        url: http://www.latex-project.org/lppl/lppl-1-3.txt
    -
       name: MIT
       url: https://opensource.org/licenses/MIT
       text: >
            Permission is hereby granted, free of charge, to any person obtaining a copy
            of this software and associated documentation files (the "Software"), to deal
            in the Software without restriction, including without limitation the rights
            to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the Software is
            furnished to do so, subject to the following conditions:
            
            The above copyright notice and this permission notice shall be included in
            all copies or substantial portions of the Software.
            
            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
            IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
            FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
            AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
            LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
            OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
            THE SOFTWARE.
```

## hyph-mr

Files: `hyph-mr.pat.txt`

```
title: Hyphenation patterns for Marathi
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences, at your option:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-mul-ethi

Files: `hyph-mul-ethi.pat.txt`

```
title: Hyphenation patterns for languages written in the Ethiopic script
copyright: Copyright (C) 2011, 2016 Arthur Reutenauer
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - name: MIT
    - url: https://opensource.org/licenses/MIT
    - text: >
        This file is available under the terms of the MIT licence.
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the “Software”), to deal
        in the Software without restriction, including without limitation the rights to
        use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
        of the Software, and to permit persons to whom the Software is furnished to do
        so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
```

## hyph-nb

Files: `hyph-nb.pat.txt`, `hyph-nb.hyp.txt`

```
title: Hyphenation patterns for Norwegian, bokmål
copyright: Copyright (C) 2004–2005 Rune Kleveland, Ole Michael Selberg, 2007 Karl Ove Hufthammer
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    text: >
        Copying and distribution of this file, with or without modification,
        are permitted in any medium without royalty, provided the copyright
        notice and this notice are preserved.
```

## hyph-nl

Files: `hyph-nl.pat.txt`, `hyph-nl.hyp.txt`

```
title: Hyphenation patterns for Dutch
copyright: Copyright (C) 1996 Piet Tutelaers
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
```

## hyph-nn

Files: `hyph-nn.pat.txt`, `hyph-nn.hyp.txt`

```
title: Hyphenation patterns for Norwegian, nynorsk
copyright: Copyright (C) 2007 Karl Ove Hufthammer
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    text: >
        Copying and distribution of this file, with or without modification,
        are permitted in any medium without royalty, provided the copyright
        notice and this notice are preserved.
```

## hyph-oc

Files: `hyph-oc.pat.txt`

```
title: Hyphenation patterns for Occitan
copyright: Copyright (C) 2016 Claudio Beccari
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the “Software”), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LPPL
        version: 1
        or_later: true
        url: https://latex-project.org/lppl/
```

## hyph-or

Files: `hyph-or.pat.txt`

```
title: Hyphenation patterns for Oriya
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the “Software”), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-pa

Files: `hyph-pa.pat.txt`

```
title: Hyphenation patterns for Panjabi
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the “Software”), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-pi

Files: `hyph-pi.pat.txt`

```
copyright: Copyright (C) 2018 Wie-Ming Cittānurakkho Bhikkhu
title: Hyphenation patterns for Pāli
notice: >
    This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person
        obtaining a copy of this software and associated documentation
        files (the “Software”), to deal in the Software without
        restriction, including without limitation the rights to use,
        copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the
        Software is furnished to do so, subject to the following
        conditions:

        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
        OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
        HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
        WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
        FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
        OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-pl

Files: `hyph-pl.pat.txt`, `hyph-pl.hyp.txt`

```
title: Hyphenation patterns for Polish
copyright: Copyright (C) 1987-1995 Hanna Kołodziejska, Bogusław Jackowski, Marek Ryćko
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is made available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the “Software”), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    - text: >
        This macro file belongs to the public domain
        under the conditions specified by the author of TeX:

           “Macro files like PLAIN.TEX should not be changed in any way,
            except with respect to preloaded fonts,
            unless the changes are authorized by the authors of the macros.”

                                                  Donald E. Knuth
```

## hyph-pms

Files: `hyph-pms.pat.txt`

```
title: Hyphenation patterns for Piedmontese
copyright: Copyright (C) 2013 Claudio Beccari
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LPPL
        version: 1.3
        or_later: true
        url: https://latex-project.org/lppl/
        status: maintained
        maintainer: Claudio Beccari, e-mail claudio dot beccari at gmail dot com
```

## hyph-pt

Files: `hyph-pt.pat.txt`, `hyph-pt.hyp.txt`

```
title: Hyphenation patterns for Portuguese
copyright: Copyright (C) 1987, 1994, 1996, 2015 Pedro J. de Rezende, 1996, 2015 J. Joao Dias Almeida, 2024 Leonardo Araujo and Aline Benevides
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: BSD 3-clause licence
    url: https://opensource.org/licenses/BSD-3-Clause
    text: >
        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions
        are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the
          distribution.
        * Neither the name of the University of Campinas, of the University
          of Minho nor the names of its contributors may be used to endorse
          or promote products derived from this software without specific
          prior written permission.

        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
        A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PEDRO J. DE
        REZENDE OR J.JOAO DIAS ALMEIDA BE LIABLE FOR ANY DIRECT, INDIRECT,
        INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
        BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
        OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
        AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
        LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
        WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
        POSSIBILITY OF SUCH DAMAGE.
```

## hyph-rm

Files: `hyph-rm.pat.txt`

```
title: Hyphenation patterns for Romansh
copyright: Copyright (C) 2012 Claudio Beccari, 2024 far.ch
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file may be distributed under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LPPL
        version: 1.3
        or_later: true
        status: maintained
        maintainer: far.ch, da@far.ch
```

## hyph-ro

Files: `hyph-ro.pat.txt`

```
title: Hyphenation patterns for Romanian
copyright: Copyright (C) 1995-1996 Adrian Rezus
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - text: [None]
```

## hyph-ru

Files: `hyph-ru.pat.txt`, `hyph-ru.hyp.txt`

```
title: Hyphenation patterns for Russian
copyright: Copyright (C) 1999-2003 Alexander I. Lebedev
notice:
    This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.2
    or_later: true
    url: https://latex-project.org/lppl/
```

## hyph-sa

Files: `hyph-sa.pat.txt`

```
title: Hyphenation patterns for Sanskrit and Prakrit, Latin transliteration,
    and Devanāgari, Bengali, Gujarati, Kannada, Malayalam, and Telugu scripts
copyright: Copyright (C) 2006-2011 Yves Codet
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    text: You may freely use, copy, modify and/or distribute this file.
```

## hyph-sh-cyrl

Files: `hyph-sh-cyrl.pat.txt`, `hyph-sh-cyrl.hyp.txt`

```
title: Hyphenation patterns for Serbo-Croatian, Cyrillic script
copyright: Copyright (C) 1990, 2008 Dejan Muhamedagić
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1
    or_later: true
    url: https://latex-project.org/lppl/
```

## hyph-sh-latn

Files: `hyph-sh-latn.pat.txt`, `hyph-sh-latn.hyp.txt`

```
title: Hyphenation patterns for Serbo-Croatian, Latin script
copyright: Copyright (C) 1990, 2008 Dejan Muhamedagić
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1
    or_later: true
    url: https://latex-project.org/lppl/
```

## hyph-sk

Files: `hyph-sk.pat.txt`, `hyph-sk.hyp.txt`

```
title: Hyphenation patterns for Slovak
copyright: Copyright (C) 1992 Jana Chlebíková
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: http://www.opensource.org/licenses/MIT
```

## hyph-sl

Files: `hyph-sl.pat.txt`

```
title: Hyphenation patterns for Slovenian
copyright: Copyright (C) 1990 Matjaž Vrečko
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of these licences:
    -
        name: LPPL
        version: 1
        or_later: true
        url: http://www.latex-project.org/lppl/lppl-1-0.html
    -
        name: MIT
        url: https://opensource.org/licences/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-sq

Files: `hyph-sq.pat.txt`

```
title: Hyphenation patterns for Albanian
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.

copyright: >
    Copyright (C) 2020 Claudio Beccari, Sabina Koliqi
              (C) 2025 Arthur Rosendahl

licence:
    name: MIT
    url:  http://opensource.org/licenses/mit-license.php
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

## hyph-sr-cyrl

Files: `hyph-sr-cyrl.pat.txt`, `hyph-sr-cyrl.hyp.txt`

```
title: Hyphenation patterns for Serbian, Cyrillic script
copyright: Copyright (C) 1990-2003 Dejan Muhamedagić, Aleksandar Jelenak
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: GPL
    url: http://www.gnu.org/copyleft/gpl.html
```

## hyph-sv

Files: `hyph-sv.pat.txt`

```
title: Hyphenation patterns for Swedish
copyright: Copyright (C) 1994 Jan Michael Rynning
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.2
    or_later: true
```

## hyph-ta

Files: `hyph-ta.pat.txt`

```
title: Hyphenation patterns for Tamil
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-te

Files: `hyph-te.pat.txt`

```
title: Hyphenation patterns for Telugu
copyright: Copyright (C) 2016 Santhosh Thottingal
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
        text: >
            Permission is hereby granted, free of charge, to any person
            obtaining a copy of this software and associated documentation
            files (the "Software"), to deal in the Software without
            restriction, including without limitation the rights to use,
            copy, modify, merge, publish, distribute, sublicense, and/or sell
            copies of the Software, and to permit persons to whom the
            Software is furnished to do so, subject to the following
            conditions:

            The above copyright notice and this permission notice shall be
            included in all copies or substantial portions of the Software.

            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
            OTHER DEALINGS IN THE SOFTWARE.
    -
        name: LGPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/lgpl.html
    -
        name: GPL
        version: 3
        or_later: true
        url: http://www.gnu.org/licenses/gpl.html
```

## hyph-th

Files: `hyph-th.pat.txt`

```
title: Hyphenation patterns for Thai
copyright: Copyright (C) 2012-2013 Theppitak Karoonboonyanan
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1.3
    or_later: true
    status: maintained
    maintainer: Theppitak Karoonboonyanan
    url: https://latex-project.org/lppl/
```

## hyph-tk

Files: `hyph-tk.pat.txt`

```
title: Hyphenation patterns for Turkmen
copyright: Copyright (C) 2010-2015 Nazar Annagurban
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: MIT
    url: https://opensource.org/licenses/MIT
    text: >
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:
        
        The above copyright notice and this permission notice shall be included in
        all copies or substantial portions of the Software.
        
        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
        THE SOFTWARE.
```

## hyph-tr

Files: `hyph-tr.pat.txt`

```
title: Hyphenation patterns for Turkish
copyright: Copyright (C) 1987 Pierre A. MacKay, 2008, 2011 TUG
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    name: LPPL
    version: 1
    or_later: true
    url: https://latex-project.org/lppl/lppl-1-0.html
```

## hyph-uk

Files: `hyph-uk.pat.txt`

```
title: Hyphenation patterns for Ukrainian
copyright: Copyright (C) 1998-2001 Maksym Polyakov
notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.
licence:
    - This file is available under any of the following licences:
    -
        name: MIT
        url: https://opensource.org/licenses/MIT
    -
        name: LPPL
        url: https://latex-project.org/lppl/
```

## hyph-zh-latn-pinyin

Files: `hyph-zh-latn-pinyin.pat.txt`

```
title: Hyphenation patterns for Chinese pinyin (Mandarin), with tone
       markers

notice: This file is part of the hyph-utf8 package.
    See http://www.hyphenation.org/tex for more information.

copyright: Copyright (C) 1994-2018 Werner Lemberg

licence:
    name: MIT
    url:  http://opensource.org/licenses/mit-license.php
    text: >
          Permission is hereby granted, free of charge, to any person
          obtaining a copy of this software and associated documentation
          files (the “Software”), to deal in the Software without
          restriction, including without limitation the rights to use,
          copy, modify, merge, publish, distribute, sublicense, and/or
          sell copies of the Software, and to permit persons to whom the
          Software is furnished to do so, subject to the following
          conditions:

          The above copyright notice and this permission notice shall be
          included in all copies or substantial portions of the Software.

          THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
          EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
          OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
          NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
          HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
          WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
          FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
          OTHER DEALINGS IN THE SOFTWARE.
```

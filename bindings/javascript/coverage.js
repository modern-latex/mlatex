// Writes assets/fallback/fonts.json: each face mLaTeX lends a web page for a
// script or symbols it carries no face of, and the characters it draws, as
// ranges of code points. A page reads it to know which face to fetch for the
// characters screen.missing() names, and fetches nothing it does not need.
//
//   node bindings/javascript/coverage.js
const fs = require("node:fs");
const path = require("node:path");

const folder = path.join(__dirname, "..", "..", "assets", "fallback");

/** The code points a font's character map draws: its Unicode subtable, format 4 or 12. */
function codes(bytes) {
	const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
	const tables = view.getUint16(4);
	let cmap = -1;
	for (let index = 0; index < tables; index++) {
		const record = 12 + index * 16;
		if (String.fromCharCode(...bytes.subarray(record, record + 4)) === "cmap") cmap = view.getUint32(record + 8);
	}
	if (cmap < 0) return [];
	// The fullest Unicode subtable there is: format 12, which reaches past
	// the first plane, before format 4.
	let best = -1;
	let format = 0;
	for (let index = 0; index < view.getUint16(cmap + 2); index++) {
		const record = cmap + 4 + index * 8;
		const platform = view.getUint16(record);
		const encoding = view.getUint16(record + 2);
		const offset = cmap + view.getUint32(record + 4);
		const kind = view.getUint16(offset);
		const unicode = platform === 0 || (platform === 3 && (encoding === 1 || encoding === 10));
		if (unicode && (kind === 12 || kind === 4) && kind > format) {
			best = offset;
			format = kind;
		}
	}
	const found = [];
	if (format === 12) {
		for (let group = 0; group < view.getUint32(best + 12); group++) {
			const at = best + 16 + group * 12;
			for (let code = view.getUint32(at); code <= view.getUint32(at + 4); code++) found.push(code);
		}
	} else if (format === 4) {
		const segments = view.getUint16(best + 6) / 2;
		const ends = best + 14;
		const starts = ends + segments * 2 + 2;
		const deltas = starts + segments * 2;
		const offsets = deltas + segments * 2;
		for (let segment = 0; segment < segments; segment++) {
			const start = view.getUint16(starts + segment * 2);
			const end = view.getUint16(ends + segment * 2);
			const delta = view.getInt16(deltas + segment * 2);
			const offset = view.getUint16(offsets + segment * 2);
			for (let code = start; code <= end && code !== 0xffff; code++) {
				const glyph =
					offset === 0
						? (code + delta) & 0xffff
						: view.getUint16(offsets + segment * 2 + offset + (code - start) * 2);
				if (glyph !== 0) found.push(code);
			}
		}
	}
	return found;
}

// The order a page is to choose in, the first face that draws a character
// the one fetched: the symbols' small faces before any script's, and the
// emoji's and the large CJK face, which draw many symbols too, last of all,
// so a check mark never costs a page the CJK face.
const last = ["NotoEmoji-Regular.ttf", "NotoSerifCJK-Regular.otf"];
const order = (name) => (name.startsWith("NotoSansSymbols") ? 0 : last.includes(name) ? 2 + last.indexOf(name) : 1);
const fonts = {};
for (const name of fs
	.readdirSync(folder)
	.sort((first, second) => order(first) - order(second) || first.localeCompare(second))) {
	if (!/\.(otf|ttf)$/i.test(name)) continue;
	// Latin, its punctuation and the spaces are every carried face's; a face
	// lent for a script is fetched for that script alone.
	const drawn = codes(fs.readFileSync(path.join(folder, name))).filter((code) => code > 0x24f);
	const ranges = [];
	for (const code of drawn.sort((first, second) => first - second)) {
		const last = ranges[ranges.length - 1];
		if (last && code === last[1] + 1) last[1] = code;
		else ranges.push([code, code]);
	}
	fonts[name] = ranges;
}
fs.writeFileSync(path.join(folder, "fonts.json"), `${JSON.stringify(fonts)}\n`);
console.log(Object.entries(fonts).map(([name, ranges]) => `${name}: ${ranges.length} ranges`).join("\n"));

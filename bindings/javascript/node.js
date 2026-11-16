// The engine for Node, finding mlatex.wasm and mlatex.data beside this file:
// Emscripten's loader looks for mlatex.data where the program runs instead.
const path = require("node:path");

const mLatex = require("./mlatex.js");

/** @param {import('./mlatex').Options} [options] */
const system = (options) => mLatex({ locateFile: (name) => path.join(__dirname, name), ...options });
// The VERSION file's, which CMake writes into package.json and the release packs.
system.version = require("./package.json").version;

module.exports = system;

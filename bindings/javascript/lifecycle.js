// Public lifecycle names for the WebAssembly bindings.
mLatex = ((load) => async (options) => {
    const system = await load(options);
    system.compose = () => new system.Session();
    system.Session.prototype.dispose = system.Session.prototype.delete;
    if (system.Screen) system.Screen.prototype.dispose = system.Screen.prototype.delete;
    return system;
})(mLatex);

if (typeof module === "object" && module.exports) {
    module.exports = mLatex;
    module.exports.default = mLatex;
}

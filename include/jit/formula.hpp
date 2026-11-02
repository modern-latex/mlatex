#pragma once

namespace jit {
    /// @brief A plot's formula read once and worked out at every point --
    ///        in machine code, by asmjit, when there are enough points to be
    ///        worth it: piece 6 of jit::Jit.
    ///
    /// render::primitives::figures::Plots::calculate reads a formula's text
    /// from its first character at every point it is asked for: `\\addplot`
    /// over 25 samples reads it 25 times, a surface of 2000 by 2000 samples
    /// 4 million times, and three times that for a parametric one. TikZ's
    /// `plot` (illustrations.cpp) asks it the same way. Read once into a
    /// list of steps, a formula is a few nanoseconds a point; compiled, it
    /// is the arithmetic and nothing else.
    ///
    /// This is the one place the JIT writes machine code. Everything else in
    /// it keeps work instead of redoing it, which is where the time is; this
    /// is for documents that draw dense plots.
    ///
    /// Empty for now; what to write is below and in src/jit/formula.cpp.
    ///
    /// @par Use (planned)
    /// @code
    /// std::optional<jit::Formula> formula = jit::Formula::compose(text);   // read once
    /// if (!formula) return;                                                 // not a formula: as calculate()'s nothing
    /// if (count * rows >= 512) formula->compose();                         // machine code, where asmjit runs
    /// for (std::size_t row = 0; row < rows; ++row) {
    ///     for (std::size_t column = 0; column < count; ++column) {
    ///         const std::optional<double> height = formula->get(xs[column], ys[row]);
    ///         ...
    ///     }
    /// }
    /// @endcode
    ///
    /// @par What to write
    /// 1. **The steps.** Move the reader in Plots::calculate (plots.cpp) into
    ///    `static std::optional<Formula> compose(std::string_view text)`
    ///    unchanged -- the same precedence, `^` binding to the right and
    ///    tighter than a sign, trigonometry in degrees, TikZ's `r`, units in
    ///    points, the names `x`, `t`, `y`, `pi` and `e`, and the same list of
    ///    functions -- but where it works a value out, have it write a step
    ///    instead: a number, x, y, an operator, or a function and how many
    ///    arguments it takes. Postfix order, so working them out is a stack.
    /// 2. **`std::optional<double> get(double x, double y) const`** works the
    ///    steps out on a small stack of doubles, and returns nothing when the
    ///    result is not finite, as calculate() does. Then calculate() is
    ///    compose() and get() -- keep its signature, which the tests call --
    ///    and every caller still reads the same numbers.
    /// 3. **`void compose()`** turns the steps into a function
    ///    `double (double x, double y)` with asmjit's Compiler, which keeps
    ///    the stack in registers for you: on x86-64, x86::Compiler with
    ///    scalar SSE2 (`addsd`, `subsd`, `mulsd`, `divsd`, `sqrtsd`); on ARM64,
    ///    a64::Compiler (`fadd`, `fsub`, `fmul`, `fdiv`, `fsqrt`). Every other
    ///    function -- sin in degrees, pow, exp, ln, atan2, mod, round -- is a
    ///    call to the same C++ function get() uses, so both give the same
    ///    bits. No fused multiply-add: it rounds once where the steps round
    ///    twice, and the numbers would differ from get()'s.
    /// 4. **`void dispose()`** gives the code back to the runtime; so does
    ///    the destructor. One asmjit::JitRuntime for the process, a static
    ///    in formula.cpp, made the first time anything is compiled.
    /// 5. **When to compile.** Compiling costs some tens of microseconds;
    ///    a point read from the steps, a few nanoseconds. Compile when a plot
    ///    will ask for 512 points or more, and read the steps below that.
    /// 6. **The callers**: the curve loop and the surface loop in plots.cpp's
    ///    `\\addplot` (each now asks calculate() once per point), and TikZ's
    ///    `plot` in illustrations.cpp. A formula asked once -- a coordinate,
    ///    a length -- keeps calling calculate().
    ///
    /// @par Guards
    /// asmjit is linked into the engine everywhere but WebAssembly (the
    /// top-level CMakeLists.txt), and its two compilers each write one kind
    /// of processor's code, so compose() is three branches:
    /// @code
    /// #if !defined(__EMSCRIPTEN__) && (defined(__x86_64__) || defined(_M_X64))
    ///     // x86::Compiler
    /// #elif !defined(__EMSCRIPTEN__) && (defined(__aarch64__) || defined(_M_ARM64))
    ///     // a64::Compiler
    /// #else
    ///     // nothing: get() reads the steps
    /// #endif
    /// @endcode
    ///
    /// @par WebAssembly
    /// asmjit writes x86 and ARM code, which a WebAssembly module cannot run,
    /// so in the module get() always reads the steps -- already far faster
    /// than reading the text. A module could write a small WebAssembly
    /// function of its own from the steps and hand its bytes to JavaScript's
    /// `WebAssembly.instantiate`, through an `EM_JS` function; that is a
    /// project of its own, for once the steps are in.
    class Formula {
    };
}

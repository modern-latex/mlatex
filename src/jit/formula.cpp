/// @file
/// @brief A plot's formula read once, and compiled with asmjit: see
///        jit/formula.hpp.
///
/// Empty for now. What follows is how the steps, get() and compose() should
/// look. The asmjit calls are asmjit 1.14's, as vcpkg installs it; its own
/// headers (asmjit/x86/x86compiler.h, asmjit/arm/a64compiler.h) carry a
/// worked example of each compiler at the top.
#include "jit/formula.hpp"

namespace jit {
    // The steps, one struct each, in postfix order:
    //
    //     struct Step {
    //         enum class Operation : std::uint8_t {
    //             Number, Across, Up,                     // a number, x, y
    //             Add, Subtract, Multiply, Divide, Power, Negate,
    //             Call,                                   // a function of one argument
    //             Pair,                                   // of two: atan2, mod, min, max, pow, veclen
    //         };
    //         Operation operation{Operation::Number};
    //         double number{0.0};                        // for Number
    //         double (*single)(double){nullptr};         // for Call: the same function get() calls
    //         double (*pair)(double, double){nullptr};   // for Pair
    //     };
    //     std::vector<Step> steps{};
    //     double (*native)(double, double){nullptr};    // compose()'s function, while there is one
    //
    // The functions in degrees are written once, as static functions here,
    // and both get() and the machine code call them, so the two agree:
    //
    //     static double sine(const double degrees) { return std::sin(degrees * std::numbers::pi / 180.0); }
    //
    // get(), reading the steps:
    //
    //     std::array<double, 64> stack{};               // deeper formulas are refused by compose()
    //     std::size_t depth = 0;
    //     for (const Step &step: steps) {
    //         switch (step.operation) {
    //             case Step::Operation::Number: stack[depth++] = step.number; break;
    //             case Step::Operation::Across: stack[depth++] = x; break;
    //             case Step::Operation::Add: --depth; stack[depth - 1] += stack[depth]; break;
    //             case Step::Operation::Call: stack[depth - 1] = step.single(stack[depth - 1]); break;
    //             ...
    //         }
    //     }
    //     if (native) return finite(native(x, y));      // compiled: the same answer, faster
    //
    // compose(), on x86-64 -- the Compiler gives each value a virtual
    // register and allocates the real ones, so the stack is a vector of
    // registers:
    //
    //     static asmjit::JitRuntime runtime;            // one for the process
    //     asmjit::CodeHolder code;
    //     code.init(runtime.environment(), runtime.cpuFeatures());
    //     asmjit::x86::Compiler compiler(&code);
    //
    //     asmjit::FuncNode *function = compiler.addFunc(asmjit::FuncSignature::build<double, double, double>());
    //     const asmjit::x86::Xmm across = compiler.newXmmSd("x");
    //     const asmjit::x86::Xmm up = compiler.newXmmSd("y");
    //     function->setArg(0, across);
    //     function->setArg(1, up);
    //
    //     std::vector<asmjit::x86::Xmm> stack;
    //     for (const Step &step: steps) {
    //         switch (step.operation) {
    //             case Step::Operation::Number: {
    //                 const asmjit::x86::Xmm value = compiler.newXmmSd();
    //                 compiler.movsd(value, compiler.newDoubleConst(asmjit::ConstPoolScope::kLocal, step.number));
    //                 stack.push_back(value);
    //                 break;
    //             }
    //             case Step::Operation::Across: {
    //                 const asmjit::x86::Xmm value = compiler.newXmmSd();
    //                 compiler.movsd(value, across);           // a copy: the next step may write to it
    //                 stack.push_back(value);
    //                 break;
    //             }
    //             case Step::Operation::Add: {
    //                 const asmjit::x86::Xmm right = stack.back();
    //                 stack.pop_back();
    //                 compiler.addsd(stack.back(), right);
    //                 break;
    //             }
    //             case Step::Operation::Call: {
    //                 asmjit::InvokeNode *call = nullptr;
    //                 compiler.invoke(&call, reinterpret_cast<std::uint64_t>(step.single),
    //                                 asmjit::FuncSignature::build<double, double>());
    //                 call->setArg(0, stack.back());
    //                 call->setRet(0, stack.back());
    //                 break;
    //             }
    //             ...
    //         }
    //     }
    //     compiler.ret(stack.back());
    //     compiler.endFunc();
    //     compiler.finalize();
    //     if (runtime.add(&native, &code) != asmjit::kErrorOk) native = nullptr;  // get() reads the steps
    //
    // On ARM64 it is the same shape with asmjit::a64::Compiler: values are
    // `compiler.newVecD()`, a number is loaded from
    // `compiler.newDoubleConst(...)` with `ldr`, and the operators are
    // `fadd`, `fsub`, `fmul` and `fdiv`, each with its destination first --
    // `compiler.fadd(left, left, right)`.
    //
    // dispose(): `runtime.release(native); native = nullptr;`.
    //
    // Tested in tests/jit/test_formula.cpp: for a list of formulas --
    // `x^2 - 3*sin(deg(x))`, `-x^2`, `sqrt(x*x + y*y)`, `atan2(y, x)`,
    // `2*x r`, `veclen(3pt,4pt)` -- over a grid of x and y, assert get()
    // before compose() and after it equal calculate() to the bit, and that
    // broken text and `1/0` give nothing, as they do now.
}

#include "jit/formula.hpp"

#include <cassert>
#include <type_traits>

// A Formula, a plot's formula read once and worked out at every point. It
// holds nothing yet, so this only shows the header stands on its own; once
// it holds its steps, the check below fails on purpose -- replace it with
// these:
//
//     for `x^2 - 3*sin(deg(x))`, `-x^2`, `sqrt(x*x + y*y)`, `atan2(y, x)`,
//     `2*x r` and `veclen(3pt,4pt)`, over a grid of x and y, assert get()
//     equals render::primitives::figures::Plots::calculate() to the bit --
//     std::bit_cast<std::uint64_t> on both -- before compose() and after it;
//
//     assert compose() of broken text gives nothing, and get() of `1/x` at
//     0 gives nothing, as calculate() does;
//
//     on a machine asmjit writes code for, assert compose() made a function
//     (the member holding it is not null).

int main() {
    assert(std::is_empty_v<jit::Formula> && "empty for now: write the checks above once it holds something");
    return 0;
}

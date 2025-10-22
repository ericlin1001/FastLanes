// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/std/span.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_STD_SPAN_HPP
#define FLS_STD_SPAN_HPP

#if __cplusplus <= 201703L
#include "fls/std/tcb_span.hpp"
namespace std {
using tcb::span;
}
#endif

#include <span>

namespace fastlanes {
using std::span;
} // namespace fastlanes

#endif // FLS_STD_SPAN_HPP

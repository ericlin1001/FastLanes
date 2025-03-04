#ifndef FLS_COMMON_ALIAS_HPP
#define FLS_COMMON_ALIAS_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>

namespace fastlanes {
// For countable things
using n_t                                = uint64_t;
constexpr static n_t FIRST_IDX           = 0;
constexpr inline n_t FFOR_BASE_BYTE_SIZE = 8;
constexpr inline n_t BITMAP_SIZE         = 16;

//
using bw_t          = uint8_t;
using rle_idx_t     = uint16_t; // position of a tuple in a vec.
using base_t        = uint8_t[FFOR_BASE_BYTE_SIZE];
using bitmap_t      = uint64_t[BITMAP_SIZE];
using unit_t        = uint64_t;
using ep_t          = uint32_t;
using var_t         = uint8_t;
using idx_t         = uint32_t;
using ofs_t         = uint32_t; // todo
using bsz_t         = uint64_t; /* byte size. */
using sz_t          = uint64_t; /* size */
using hdr_field_t   = uint64_t;
using len_t         = uint32_t;
using vec_idx_t     = uint16_t; // for indexes inside a vector
using entry_point_t = uint32_t; // for indexes inside a vector

// clang-format off
template <typename T> using sp = std::shared_ptr<T>;
template <typename T> using up = std::unique_ptr<T>;

using std::make_unique;
using std::make_shared;

constexpr static n_t   INVALID_N      = std::numeric_limits<n_t>::max(); // INVALID
constexpr static len_t INVALID_LENGTH = std::numeric_limits<len_t>::max(); // INVALID
}

#endif // FLS_COMMON_ALIAS_HPP

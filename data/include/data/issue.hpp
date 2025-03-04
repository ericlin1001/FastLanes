#ifndef DATA_ISSUE_HPP
#define DATA_ISSUE_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

class Issue {
public:
	static constexpr string_view ISSUE_000 {FLS_CMAKE_SOURCE_DIR "/data/generated/issues/issue_000/"};
	static constexpr string_view ISSUE_001 {FLS_CMAKE_SOURCE_DIR "/data/generated/issues/issue_001/"};
};
} // namespace fastlanes

#endif // DATA_ISSUE_HPP

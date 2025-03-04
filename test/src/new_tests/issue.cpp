#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, issue_000) { TestCorrectness(Issue::ISSUE_000); }
TEST_F(FastLanesReaderTester, issue_001) {
	const vector<n_t> constant_cols = {};
	const vector<n_t> equal_cols    = {};
	const vector<n_t> target_column_indexes {};

	AllTest(Issue::ISSUE_001, constant_cols, equal_cols, target_column_indexes);
}
} // namespace fastlanes
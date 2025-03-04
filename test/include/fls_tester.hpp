#ifndef FLS_TESTER_HPP
#define FLS_TESTER_HPP

#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include "gtest/gtest.h"

namespace fastlanes {
class FastLanesReaderTester : public ::testing::Test {
	const path fastlanes_repo_data_path {FLS_CMAKE_SOURCE_DIR};
	const path fls_dir_path = fastlanes_repo_data_path / "data" / "fls";
	path       fls_file_path_process_specific;
	path       fls_dir_path_process_specific;

	void SetUp() override {
		fls_dir_path_process_specific  = fls_dir_path / std::to_string(getpid());
		fls_file_path_process_specific = fls_dir_path_process_specific / "data.fls";
		if (!exists(fls_dir_path_process_specific)) {
			create_directories(fls_dir_path_process_specific);
		}
	};

	void TearDown() override {
		if (exists(fls_dir_path_process_specific)) {
			remove_all(fls_dir_path_process_specific);
		}
	}

public:
	void TestCorrectness(const string_view table, const vector<OperatorToken>& expressions = {}) const {
		const path dir_path = fastlanes_repo_data_path / string(table);

		// original rowgroup
		Connection con1;
		if (!expressions.empty()) {
			con1.reset().force_schema_pool(expressions).read(dir_path);
		} else {
			con1.reset().read(dir_path);
		}
		const auto& original_rowgroup = con1.rowgroup();

		// to_fls
		con1.to_fls(fls_dir_path_process_specific);

		// decoded rowgroup
		Connection con2;
		auto&      fls_reader       = con2.reset().read_fls(fls_dir_path_process_specific);
		const auto decoded_rowgroup = fls_reader.materialize();
		decoded_rowgroup->Finalize();

		// Compare rowgroups
		std::variant<bool, n_t> result = (original_rowgroup == *decoded_rowgroup);
		if (std::holds_alternative<bool>(result)) {
			ASSERT_TRUE(std::get<bool>(result));
		} else {
			ASSERT_TRUE(false) << "Rowgroups differ at column index: " << std::get<n_t>(result) << " ❌" << std::endl;
		}

		// Validate file size
		const auto file_size = std::filesystem::file_size(fls_file_path_process_specific);
		ASSERT_EQ(file_size, fls_reader.footer().m_rowgroup_size);
	}

	void TestConstantness(const vector<n_t>& constant_indexes) const {
		Connection  con;
		const auto& fls_reader = con.reset().read_fls(fls_dir_path_process_specific);
		const auto& footer     = fls_reader.footer();

		for (const auto col_idx : constant_indexes) {
			//
			auto& col_descriptor = footer.GetColumnDescriptors()[col_idx];
			ASSERT_EQ(col_descriptor.total_size, 0) << col_idx << " should be constant";
		}
	}

	void TestEquality(const string_view table) const {
		TestCorrectness(table);

		// decoded rowgroup
		Connection  con2;
		const auto& fls_reader = con2.reset().read_fls(fls_dir_path_process_specific);
		const auto  footer     = fls_reader.footer();

		for (n_t col_idx = 1; col_idx < footer.size(); ++col_idx) {
			ASSERT_EQ(footer[col_idx].total_size, 0) << col_idx << " should be of size 0";
		}
	}

	void TestEquality(const vector<n_t>& equal_cols) const {
		Connection  con;
		const auto& fls_reader = con.reset().read_fls(fls_dir_path_process_specific);
		const auto  footer     = fls_reader.footer();

		for (const auto col_index : equal_cols) {
			auto& col_descriptor = footer.GetColumnDescriptors()[col_index];
			ASSERT_EQ(col_descriptor.total_size, 0) << "size of column " << col_index << ":" << col_descriptor.name
			                                        << " should be 0, as it is equal to another col.";
		}
	}

	void TestMap1To1(const vector<n_t>& target_column_indexes) const {
		Connection  con;
		const auto& fls_reader = con.reset().read_fls(fls_dir_path_process_specific);
		const auto  footer     = fls_reader.footer();

		for (const auto col_index : target_column_indexes) {
			auto& col_descriptor = footer.GetColumnDescriptors()[col_index];
			ASSERT_TRUE(is_1_to_1(col_descriptor.encoding_rpn.operator_tokens[0])) << "  " << col_index;
		}
	}

	void AllTest(const string_view  table,
	             const vector<n_t>& constant_indexes,
	             const vector<n_t>& equal_cols,
	             const vector<n_t>& target_column_indexes) const {
		//
		TestCorrectness(table);
		TestConstantness(constant_indexes);
		TestMap1To1(target_column_indexes);
		TestEquality(equal_cols);
	}
};
} // namespace fastlanes

#endif // FLS_TESTER_HPP

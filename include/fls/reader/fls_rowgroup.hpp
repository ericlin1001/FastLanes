#ifndef FLS_READER_FLS_ROWGROUP_HPP
#define FLS_READER_FLS_ROWGROUP_HPP

#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Footer;
class ColumnView;
/*--------------------------------------------------------------------------------------------------------------------*/

class RowgroupView {
public:
	explicit RowgroupView(span<std::byte> ptr, const Footer& footer);

public:
	ColumnView&       operator[](n_t col_idx);
	const ColumnView& operator[](n_t col_idx) const;

public:
	vector<up<ColumnView>> columns;
};

} // namespace fastlanes

#endif // FLS_READER_FLS_ROWGROUP_HPP

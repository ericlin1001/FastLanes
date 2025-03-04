#ifndef FLS_ENCODER_MATERIALIZER_HPP
#define FLS_ENCODER_MATERIALIZER_HPP

#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
class Vec;
class Rowgroup;
class PhysicalExpr;

template <typename PT>
class SingleColumnMaterializer {
public:
	explicit SingleColumnMaterializer(span<PT> output_span);

public:
	void Materialize(const Vec& vec);

public:
	span<PT> output_span;
};

class Materializer {
public:
	explicit Materializer(Rowgroup& rowgroup);
	void Materialize(const vector<sp<PhysicalExpr>>& expressions, n_t vec_idx) const;

public:
	Rowgroup& rowgroup;
};

} // namespace fastlanes
#endif // FLS_ENCODER_MATERIALIZER_HPP

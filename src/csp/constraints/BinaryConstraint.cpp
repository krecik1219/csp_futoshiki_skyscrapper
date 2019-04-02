#include "BinaryConstraint.hpp"

namespace csp {

BinaryConstraint::BinaryConstraint(const Variable& first, const Variable& second, std::function)
	: first(first)
	, second(second)
{
}

} // namespace csp


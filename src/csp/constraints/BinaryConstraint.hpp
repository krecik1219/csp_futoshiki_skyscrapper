#pragma once

#include "Constraint.hpp"
#include <csp/Variable.hpp>

namespace csp {

class BinaryConstraint : public Constraint
{
public:
	BinaryConstraint(const Variable& first, const Variable& second);

private:
	const Variable& first;
	const Variable& second;
};

} // namespace csp

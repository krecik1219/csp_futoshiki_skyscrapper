#pragma once

#include <vector>
#include <memory>

#include "Constraint.hpp"

namespace csp {

class ConstraintsContainer
{
public:
	ConstraintsContainer();
	ConstraintsContainer(std::vector<std::unique_ptr<Constraint>>&& constraints);

	void setConstraints(std::vector<std::unique_ptr<Constraint>>&& constraints);

private:
	std::vector<std::unique_ptr<Constraint>> constraints;
};

} // namespace csp

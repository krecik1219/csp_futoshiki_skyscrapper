#include "ConstraintsContainer.hpp"

namespace csp {

ConstraintsContainer::ConstraintsContainer() = default;

ConstraintsContainer::ConstraintsContainer(std::vector<std::unique_ptr<Constraint>>&& constraints)
	: constraints(std::move(constraints))
{
}

void ConstraintsContainer::setConstraints(std::vector<std::unique_ptr<Constraint>>&& constraintsVec)
{
	constraints = std::move(constraintsVec);
}

} // namespace csp

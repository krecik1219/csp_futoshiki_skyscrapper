#pragma once

#include <vector>
#include <memory>

#include "Constraint.hpp"
#include <csp/Variables/Variable.hpp>

namespace csp {

template<class ValueType>
class ConstraintsContainer
{
public:
	using ConstrPtr = std::unique_ptr<Constraint<ValueType>>;

	ConstraintsContainer();
	ConstraintsContainer(std::vector<ConstrPtr>&& constraints);

	void setConstraints(std::vector<ConstrPtr>&& constraints);
	void addConstraint(ConstrPtr&& constraint);
	bool areConstraintsForVarSatisfied(const Variable<ValueType>* var) const;

private:
	std::vector<ConstrPtr> constraints;
};

template<class ValueType>
ConstraintsContainer<ValueType>::ConstraintsContainer() = default;

template<class ValueType>
ConstraintsContainer<ValueType>::ConstraintsContainer(std::vector<ConstrPtr>&& constraints)
	: constraints(std::move(constraints))
{
}

template<class ValueType>
void ConstraintsContainer<ValueType>::setConstraints(std::vector<ConstrPtr>&& constraintsVec)
{
	constraints = std::move(constraintsVec);
}

template<class ValueType>
void ConstraintsContainer<ValueType>::addConstraint(ConstrPtr&& constraint)
{
	constraints.push_back(std::move(constraint));
}

template<class ValueType>
bool ConstraintsContainer<ValueType>::areConstraintsForVarSatisfied(const Variable<ValueType>* var) const
{
	// TODO: use STL
	for (const auto& constr : constraints)
	{
		if (constr->isAboutVar(var) && constr->areConstraintVariablesAssigned() && !(*constr)())
			return false;

	}
	return true;
}

} // namespace csp

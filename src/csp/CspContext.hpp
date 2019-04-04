#pragma once

#include <algorithm>
#include <vector>
#include <memory>

#include "variables/Variable.hpp"
#include "constraints/ConstraintsContainer.hpp"

namespace csp {

template<class ValueType>
class CspContext
{
public:
	using VarPtr = std::unique_ptr<Variable<ValueType>>;

	CspContext(std::vector<VarPtr>&& variables, ConstraintsContainer<ValueType>&& constraints);

	std::vector<VarPtr>& getVariables();
	Variable<ValueType>* getUnassignedVariable();
	void addConstraint(std::unique_ptr<Constraint<ValueType>>&& constraint);
	bool isAssignmentComplete() const;
	bool areConstraintsSatisfied(const Variable<ValueType>* var) const;

private:
	std::vector<VarPtr> variables;
	ConstraintsContainer<ValueType> constraints;
};

template<class ValueType>
CspContext<ValueType>::CspContext(std::vector<VarPtr>&& variables, ConstraintsContainer<ValueType>&& constraints)
	: variables(std::move(variables))
	, constraints(std::move(constraints))
{
}

template<class ValueType>
std::vector<typename CspContext<ValueType>::VarPtr>& CspContext<ValueType>::getVariables()
{
	return variables;
}

template<class ValueType>
Variable<ValueType>* CspContext<ValueType>::getUnassignedVariable()
{
	for (auto& var : variables)
	{
		if (!var->isAssigned())
			return var.get();
	}

	return nullptr;
}

template<class ValueType>
void CspContext<ValueType>::addConstraint(std::unique_ptr<Constraint<ValueType>>&& constraint)
{
	constraints.addConstraint(std::move(constraint));
}

template<class ValueType>
bool CspContext<ValueType>::isAssignmentComplete() const
{
	return std::all_of(variables.cbegin(), variables.cend(),
		[](const auto& var) {return var->isAssigned(); });
}

template<class ValueType>
bool CspContext<ValueType>::areConstraintsSatisfied(const Variable<ValueType>* var) const
{
	return constraints.areConstraintsForVarSatisfied(var);
}

} // namespace csp

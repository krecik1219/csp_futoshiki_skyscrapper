#pragma once

#include <algorithm>
#include <functional>

#include "Constraint.hpp"
#include <csp/variables/Variable.hpp>

namespace csp {

template <class ValueType>
class MultiConstraint : public Constraint<ValueType>
{
public:
	using Var = Variable<ValueType>;

	MultiConstraint(std::vector<Var*>&& variables,
		const std::function<bool(const std::vector<Var*>&)>& variablesCheckFn);

	virtual bool isAboutVar(const Var* var) const override;
	virtual bool areConstraintVariablesAssigned() const override;

protected:
	virtual bool check() override;

private:
	const std::vector<Var*> variables;
	const std::function<bool(const std::vector<Var*>&)> variablesCheckFn;
};

template<class ValueType>
MultiConstraint<ValueType>::MultiConstraint(std::vector<Var*>&& variables, const std::function<bool(const std::vector<Var*>&)>& variablesCheckFn)
	: variables(std::move(variables))
	, variablesCheckFn(variablesCheckFn)
{
}

template<class ValueType>
bool MultiConstraint<ValueType>::isAboutVar(const Var* var) const
{
	// TODO use STL
	for (const auto& v : variables)
	{
		if (v == var)
			return true;
	}
	return false;
}

template<class ValueType>
bool MultiConstraint<ValueType>::areConstraintVariablesAssigned() const
{
	return std::all_of(variables.cbegin(), variables.cend(),
		[](const auto& var) {return var->isAssigned(); });
}

template<class ValueType>
bool MultiConstraint<ValueType>::check()
{
	return variablesCheckFn(variables);
}

} // namespace csp

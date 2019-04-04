#pragma once

#include <functional>

#include "Constraint.hpp"
#include <csp/Variables/Variable.hpp>

namespace csp {

template<class ValueType>
class BinaryConstraint : public Constraint<ValueType>
{
public:
	BinaryConstraint(const Variable<ValueType>& first, const Variable<ValueType>& second,
		const std::function<bool(const Variable<ValueType>&, const Variable<ValueType>&)>& variablesCheckFn);

	virtual bool isAboutVar(const Variable<ValueType>* var) const override;
	virtual bool areConstraintVariablesAssigned() const override;

protected:
	virtual bool check() override;

private:
	const Variable<ValueType>& first;
	const Variable<ValueType>& second;
	const std::function<bool(const Variable<ValueType>&, const Variable<ValueType>&)> variablesCheckFn;
};

template<class ValueType>
BinaryConstraint<ValueType>::BinaryConstraint(const Variable<ValueType>& first, const Variable<ValueType>& second, \
	const std::function<bool(const Variable<ValueType>&, const Variable<ValueType>&)>& variablesCheckFn)
	: first(first)
	, second(second)
	, variablesCheckFn(variablesCheckFn)
{
}

template<class ValueType>
bool BinaryConstraint<ValueType>::isAboutVar(const Variable<ValueType>* var) const
{
	return &first == var || &second == var;
}

template<class ValueType>
bool BinaryConstraint<ValueType>::areConstraintVariablesAssigned() const
{
	return first.isAssigned() && second.isAssigned();
}

template<class ValueType>
bool BinaryConstraint<ValueType>::check()
{
	return variablesCheckFn(first, second);
}

} // namespace csp

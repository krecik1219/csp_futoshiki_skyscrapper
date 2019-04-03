#pragma once

#include <functional>

#include "Constraint.hpp"
#include <csp/Variable.hpp>

namespace csp {

template<class ValueType>
class BinaryConstraint : public Constraint
{
public:
	BinaryConstraint(const Variable<ValueType>& first, const Variable<ValueType>& second,
		const std::function<bool(const Variable<ValueType>&, const Variable<ValueType>&)>& variablesCheckFn);

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
bool BinaryConstraint<ValueType>::check()
{
	return variablesCheckFn(first, second);
}

} // namespace csp

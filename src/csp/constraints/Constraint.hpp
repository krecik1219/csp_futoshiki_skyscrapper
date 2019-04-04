#pragma once

#include <csp/Variables/Variable.hpp>

namespace csp {

template <class ValueType>
class Constraint
{
public:
	Constraint();
	virtual ~Constraint();

	Constraint(const Constraint&) = delete;
	Constraint& operator=(const Constraint&) = delete;
	Constraint(Constraint&&) = delete;
	Constraint& operator=(Constraint&&) = delete;

	virtual bool operator() () final;
	virtual bool isAboutVar(const Variable<ValueType>* var) const = 0;
	virtual bool areConstraintVariablesAssigned() const = 0;

protected:
	virtual bool check() = 0;
};

template <class ValueType>
Constraint<ValueType>::Constraint() = default;

template <class ValueType>
Constraint<ValueType>::~Constraint() = default;

template <class ValueType>
bool Constraint<ValueType>::operator()()
{
	return check();
}

} // namespace csp

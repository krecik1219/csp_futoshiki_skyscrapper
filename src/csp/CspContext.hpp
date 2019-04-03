#pragma once

#include <vector>
#include <memory>

#include "Variable.hpp"
#include "constraints/ConstraintsContainer.hpp"

namespace csp {

template<class ValueType>
class CspContext
{
public:
	using VarPtr = std::unique_ptr<Variable<ValueType>>;

	CspContext(std::vector<VarPtr>&& variables, ConstraintsContainer&& constraints);

	std::vector<VarPtr>& getVariables();

private:
	std::vector<VarPtr> variables;
	ConstraintsContainer constraints;
};

template<class ValueType>
CspContext<ValueType>::CspContext(std::vector<VarPtr>&& variables, ConstraintsContainer&& constraints)
	: variables(std::move(variables))
	, constraints(std::move(constraints))
{
}

template<class ValueType>
std::vector<typename CspContext<ValueType>::VarPtr>& CspContext<ValueType>::getVariables()
{
	return variables;
}

} // namespace csp

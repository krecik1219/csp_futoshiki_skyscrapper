#pragma once

#include <csp/CspContext.hpp>
#include <csp/Variables/Variable.hpp>

namespace csp {

template <class ValueType>
class Backtracking
{
public:
	using Var = Variable<ValueType>;
	using Solution = std::vector<std::unique_ptr<Var>>;

	Backtracking(CspContext<ValueType>& cspContext);

	void solve();

private:
	CspContext<ValueType>& cspContext;
	std::vector<Solution> solutions;
};

template<class ValueType>
Backtracking<ValueType>::Backtracking(CspContext<ValueType>& cspContext)
	: cspContext(cspContext)
{
}

template<class ValueType>
void Backtracking<ValueType>::solve()
{
	// TODO optimize for example: check only constraints that are connected with THE var
	if (cspContext.isAssignmentComplete())
	{
		const auto& vars = cspContext.getVariables();
		Solution solution;
		solution.reserve(vars.size());
		std::transform(vars.cbegin(), vars.cend(), std::back_inserter(solution),
			[](const auto& v) {return std::make_unique<Variable<int32_t>>(*v); });
		solutions.push_back(std::move(solution));
		return;
	}

	Var* var = cspContext.getUnassignedVariable();

	if (var == nullptr)
		throw std::runtime_error("Backtracking algorithm internal error, variables assignment inconsistency");

	for (const auto& value : var->getDomain().getDomainValues())
	{
		var->setValue(value);
		if (cspContext.areConstraintsSatisfied(var))
		{
			solve();
		}
		else
		{
			var->reset();
		}
	}
	//if(solution.empty())
	//	var->reset();
	var->reset();
	if (var->getName() == "A2")
	{
		int x = 2;
		x++;
	}
}

} // namespace csp

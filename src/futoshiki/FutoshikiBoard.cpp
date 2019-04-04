#include "FutoshikiBoard.hpp"

#include <unordered_set>

#include <csp/constraints/MultiConstraint.hpp>

namespace csp {
namespace futo {

FutoshikiBoard::FutoshikiBoard(const uint32_t instanceSize, std::unique_ptr<CspContext<int32_t>>&& cspContextPtr)
	: instanceSize(instanceSize)
	, boardState(instanceSize)
	, cspContext(std::move(cspContextPtr))
	, backtracking(*this->cspContext)
{
	for (auto& row : boardState)
		row.resize(instanceSize);
	auto& variables = cspContext->getVariables();
	for (auto i = 0u; i < variables.size(); i++)
	{
		const uint32_t row = i / instanceSize;
		const uint32_t column = i % instanceSize;
		boardState[row][column] = variables[i].get();
	}

	// add futoshiki constraints
	auto futoshikiCheckFn =
		[](const std::vector<Var*>& vars) {
			std::unordered_set<int32_t> values;
			for (const auto& var : vars)
			{
				if (values.find(var->getValue()) == values.end())
					values.insert(var->getValue());
				else
					return false;
			}
			return true;
		};
	// rows
	for (auto i = 0u; i < boardState.size(); i++)
	{
		std::vector<Var*> varsPtrsVec;
		for (auto j = 0; j < boardState.size(); j++)
		{
			varsPtrsVec.push_back(boardState[i][j]);
		}
		cspContext->addConstraint(
			std::make_unique<MultiConstraint<int32_t>>(std::move(varsPtrsVec), futoshikiCheckFn)
		);
	}
	// columns
	for (auto i = 0u; i < boardState.size(); i++)
	{
		std::vector<Var*> varsPtrsVec;
		for (auto j = 0; j < boardState.size(); j++)
		{
			varsPtrsVec.push_back(boardState[j][i]);
		}
		cspContext->addConstraint(
			std::make_unique<MultiConstraint<int32_t>>(std::move(varsPtrsVec), futoshikiCheckFn)
		);
	}
}

void FutoshikiBoard::solve()
{
	backtracking.solve();
}

} // namespace futo
} // namespace csp


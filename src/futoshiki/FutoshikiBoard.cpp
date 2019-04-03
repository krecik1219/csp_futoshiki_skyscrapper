#include "FutoshikiBoard.hpp"

namespace csp {
namespace futo {

FutoshikiBoard::FutoshikiBoard(const uint32_t instanceSize, std::unique_ptr<CspContext<int32_t>>&& cspContextPtr)
	: instanceSize(instanceSize)
	, boardState(instanceSize)
	, cspContext(std::move(cspContextPtr))
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
}

} // namespace futo
} // namespace csp


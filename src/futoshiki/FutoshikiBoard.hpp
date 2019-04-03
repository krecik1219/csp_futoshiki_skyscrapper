#pragma once

#include <cstdint>
#include <vector>
#include <csp/Variable.hpp>
#include <csp/constraints/ConstraintsContainer.hpp>
#include <csp/CspContext.hpp>

namespace csp {
namespace futo {

using Var = Variable<int32_t>;

class FutoshikiBoard
{
public:
	FutoshikiBoard(const uint32_t instanceSize, std::unique_ptr<CspContext<int32_t>>&& cspContext);

	std::vector<Var*>& operator[] (const uint32_t index)
	{
		return boardState[index];
	}

	const std::vector<Var*>& operator[] (const uint32_t index) const
	{
		return boardState[index];
	}

private:
	const uint32_t instanceSize;
	std::vector<std::vector<Var*>> boardState;
	std::unique_ptr<CspContext<int32_t>> cspContext;
};

} // namespace futo
} // namespace csp

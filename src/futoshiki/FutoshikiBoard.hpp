#pragma once

#include <cstdint>
#include <vector>

namespace csp {
namespace futo {

struct FutoshikiBoard
{
	std::vector<std::vector<uint32_t>> boardState;

	std::vector<uint32_t>& operator[] (const uint32_t index)
	{
		return boardState[index];
	}

	const std::vector<uint32_t>& operator[] (const uint32_t index) const
	{
		return boardState[index];
	}
};

} // namespace futo
} // namespace csp

#pragma once

#include <cstdint>

#include <futoshiki/FutoshikiBoard.hpp>

using namespace csp::futo;

namespace config {

class FutoInstanceConfig
{
	uint32_t size;
	FutoshikiBoard initialBoard;
};

} // namespace config

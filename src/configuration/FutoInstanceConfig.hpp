#pragma once

#include <cstdint>
#include <vector>

#include <futoshiki/FutoshikiBoard.hpp>
#include <csp/Variable.hpp>
#include <csp/constraints/ConstraintsContainer.hpp>


namespace config {

struct FutoInstanceConfig
{
	uint32_t instanceSize;
	std::vector<std::unique_ptr<csp::Variable<int32_t>>> variables;
	csp::ConstraintsContainer constraints;
};

} // namespace config

#include "Constraint.hpp"

namespace csp {

Constraint::Constraint() = default;
Constraint::~Constraint() = default;

bool Constraint::operator()()
{
	return check();
}

} // namespace csp


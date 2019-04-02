#pragma once

namespace csp {

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

protected:
	virtual bool check() = 0;
};

} // namespace csp

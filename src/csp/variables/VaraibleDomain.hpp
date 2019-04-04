#pragma once

#include <vector>

namespace csp {

template<class ValueType>
class VariableDomain
{
public:
	VariableDomain(std::vector<ValueType>&& domainValues);

	bool operator==(const VariableDomain<ValueType>& other) const;

	const std::vector<ValueType>& getDomainValues() const;

private:
	const std::vector<ValueType> domainValues;
};

template<class ValueType>
VariableDomain<ValueType>::VariableDomain(std::vector<ValueType>&& domainValues)
	: domainValues(std::move(domainValues))
{
}

template<class ValueType>
bool VariableDomain<ValueType>::operator==(const VariableDomain<ValueType>& other) const
{
	return domainValues == other.domainValues;
}

template<class ValueType>
const std::vector<ValueType>& VariableDomain<ValueType>::getDomainValues() const
{
	return domainValues;
}

} // namespace csp

#pragma once

#include <memory>
#include <string>

#include "VaraibleDomain.hpp"

namespace csp {

template <class ValueType>
class Variable
{
public:
	Variable(const std::string& variableName, const VariableDomain<ValueType>& domain, const ValueType& value);
	virtual ~Variable() = default;

	Variable(const Variable&) = delete;
	Variable& operator=(const Variable&) = delete;
	Variable(Variable&&) = delete;
	Variable& operator=(Variable&&) = delete;

	virtual bool operator==(const Variable& other);
	const std::string& getName() const;
	const ValueType& getValue() const;
	void setValue(const ValueType& value);

private:
	const std::string variableName;
	const VariableDomain<ValueType> domain;
	ValueType value;
};

template<class ValueType>
Variable<ValueType>::Variable(const std::string& variableName, const VariableDomain<ValueType>& domain, const ValueType& value)
	: variableName(variableName)
	, domain(domain)
	, value(value)
{
}

template<class ValueType>
bool Variable<ValueType>::operator==(const Variable& other)
{
	return variableName == other.variableName && domain == other.domain && value == other.value;
}

template<class ValueType>
const std::string & Variable<ValueType>::getName() const
{
	return variableName;
}

template<class ValueType>
const ValueType& Variable<ValueType>::getValue() const
{
	return value;
}

template<class ValueType>
void Variable<ValueType>::setValue(const ValueType& value)
{
	this->value = value;
}

} // namespace csp

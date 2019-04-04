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
	virtual ~Variable();

	Variable(const Variable&);
	Variable& operator=(const Variable&) = delete;
	Variable(Variable&&) = delete;
	Variable& operator=(Variable&&) = delete;

	virtual bool operator==(const Variable& other);
	const std::string& getName() const;
	const ValueType& getValue() const;
	void setValue(const ValueType& value);
	const VariableDomain<ValueType>& getDomain() const;
	bool isAssigned() const;
	void reset();

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
Variable<ValueType>::~Variable() = default;

template<class ValueType>
Variable<ValueType>::Variable(const Variable&) = default;

template<class ValueType>
bool Variable<ValueType>::operator==(const Variable& other)
{
	return variableName == other.variableName && domain == other.domain && value == other.value;
}

template<class ValueType>
const std::string& Variable<ValueType>::getName() const
{
	return variableName;
}

template<class ValueType>
const ValueType& Variable<ValueType>::getValue() const
{
	return value;
}

template<class ValueType>
void Variable<ValueType>::setValue(const ValueType& newValue)
{
	value = newValue;
}

template<class ValueType>
const VariableDomain<ValueType>& Variable<ValueType>::getDomain() const
{
	return domain;
}

template<class ValueType>
bool Variable<ValueType>::isAssigned() const
{
	return value != ValueType{};
}

template<class ValueType>
void Variable<ValueType>::reset()
{
	value = ValueType{};
}

} // namespace csp

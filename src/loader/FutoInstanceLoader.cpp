#include "FutoInstanceLoader.hpp"

#include <algorithm>
#include <exception>
#include <fstream>
#include <numeric>

#include "ConfigParsingException.hpp"
#include <utils/StringUtils.hpp>
#include <csp/Variables/VaraibleDomain.hpp>
#include <csp/Variables/Variable.hpp>
#include <csp/constraints/BinaryConstraint.hpp>
#include <csp/CspContext.hpp>


namespace loader {

csp::futo::FutoshikiBoard FutoInstanceLoader::loadFutoInstanceConfig(const std::string& filePath) const
{
	std::ifstream fileHandle(filePath);
	if (!fileHandle.is_open())
		throw std::runtime_error("Could not read file: " + filePath);

	std::vector<std::string> initialStateStrings;
	bool wasInitialStateParsed = false;
	std::vector<std::unique_ptr<csp::Constraint<int32_t>>> constraintsVec;
	config::FutoInstanceConfig futoInstanceConfig;
	std::string line;
	ReadingType readingType = ReadingType::instanceSize;
	while (std::getline(fileHandle, line))
	{
		decideWhatToDoWithLine(line, readingType, futoInstanceConfig, initialStateStrings, wasInitialStateParsed, constraintsVec);
	}
	futoInstanceConfig.constraints.setConstraints(std::move(constraintsVec));
	std::unique_ptr<csp::CspContext<int32_t>> cspContext =
		std::make_unique<csp::CspContext<int32_t>>(std::move(futoInstanceConfig.variables), std::move(futoInstanceConfig.constraints));
	return csp::futo::FutoshikiBoard(futoInstanceConfig.instanceSize, std::move(cspContext));
}

void FutoInstanceLoader::decideWhatToDoWithLine(const std::string& line, ReadingType& readingType,
	config::FutoInstanceConfig& futoInstanceConfig, std::vector<std::string>& initialStateStrings,
	bool& wasInitialStateParsed, std::vector<std::unique_ptr<csp::Constraint<int32_t>>>& constraintsVec) const
{
	if (line.find("START:") != std::string::npos)
	{
		readingType = ReadingType::initialState;
	}
	else if (line.find("REL:") != std::string::npos)
	{
		readingType = ReadingType::constraints;
	}
	else
	{
		switch(readingType)
		{
			case ReadingType::instanceSize:
			{
				readInstanceSize(line, futoInstanceConfig);

			} break;
			case ReadingType::initialState:
			{
				readInitialStateLine(line, initialStateStrings);
			} break;
			case ReadingType::constraints:
			{
				if (!wasInitialStateParsed)
				{
					parseInitialState(initialStateStrings, futoInstanceConfig);
					wasInitialStateParsed = true;
				}
				readConstraint(line, futoInstanceConfig, constraintsVec);
			} break;
			default:
				throw ConfigParsingException("Parsing error, token is not supposed to be number but did not match initial state neither constraint");
		}
	}
}

std::string FutoInstanceLoader::prepareValueToStore(const std::string& s) const
{
	std::string value = s;
	utils::str::trim(value);
	return value;
}

void FutoInstanceLoader::readInstanceSize(const std::string& line, config::FutoInstanceConfig& futoInstanceConfig) const
{
	auto value = prepareValueToStore(line);
	futoInstanceConfig.instanceSize = std::stoi(value);
}

void FutoInstanceLoader::readInitialStateLine(const std::string& line, std::vector<std::string>& initialStateStrings) const
{
	auto s = prepareValueToStore(line);
	initialStateStrings.push_back(std::move(s));
}

void FutoInstanceLoader::parseInitialState(std::vector<std::string>& initialStateStrings, config::FutoInstanceConfig& futoInstanceConfig) const
{
	uint32_t i = 0;
	std::vector<int32_t> domainValues(futoInstanceConfig.instanceSize);
	std::iota(domainValues.begin(), domainValues.end(), 1);
	csp::VariableDomain<int32_t> domain(std::move(domainValues));
	using Var = csp::Variable<int32_t>;
	std::vector<std::unique_ptr<Var>> variables;
	variables.reserve(futoInstanceConfig.instanceSize * futoInstanceConfig.instanceSize);
	for (const auto& line : initialStateStrings)
	{
		const auto splittedStr = utils::str::split(line, ';');
		if (splittedStr.size() != futoInstanceConfig.instanceSize)
			throw ConfigParsingException("Bad initial state format");
		uint32_t j = 0;
		for (const auto& token : splittedStr)
		{
			const int32_t value = std::stoi(token);
			char rowLetter = 65 + static_cast<char>(i);
			std::string varName = rowLetter + std::to_string(j + 1);
			variables.push_back(std::make_unique<Var>(varName, domain, value));
			j++;
		}
		i++;
	}
	futoInstanceConfig.variables = std::move(variables);
}

void FutoInstanceLoader::readConstraint(const std::string& line, config::FutoInstanceConfig& futoInstanceConfig,
	std::vector<std::unique_ptr<csp::Constraint<int32_t>>>& constraintsVec) const
{
	const auto splittedStr = utils::str::split(line, ';');
	if (splittedStr.size() != 2)
		throw ConfigParsingException("Wrong constraint format");
	std::string varName1 = splittedStr[0];
	std::string varName2 = splittedStr[1];
	auto varIter1 = std::find_if(futoInstanceConfig.variables.cbegin(), futoInstanceConfig.variables.cend(),
		[&varName1](const auto& var) {return var->getName() == varName1; });
	auto varIter2 = std::find_if(futoInstanceConfig.variables.cbegin(), futoInstanceConfig.variables.cend(),
		[&varName2](const auto& var) {return var->getName() == varName2; });
	if (varIter1 == futoInstanceConfig.variables.cend() || varIter2 == futoInstanceConfig.variables.cend())
		throw ConfigParsingException("No variables matching those in constraints section");
	const auto& var1 = *varIter1;
	const auto& var2 = *varIter2;
	constraintsVec.push_back(std::make_unique<csp::BinaryConstraint<int32_t>>(*var1, *var2,
		[](const auto& var1, const auto& var2) {return var1.getValue() < var2.getValue(); }));
}

} // namespace loader

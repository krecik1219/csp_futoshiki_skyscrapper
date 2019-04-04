#pragma once

#include <configuration/FutoInstanceConfig.hpp>
#include <csp/constraints/Constraint.hpp>
#include <futoshiki/FutoshikiBoard.hpp>

namespace loader {

enum class ReadingType
{
	instanceSize,
	initialState,
	constraints
};

class FutoInstanceLoader
{
public:
	csp::futo::FutoshikiBoard loadFutoInstanceConfig(const std::string& filePath) const;

private:
	void decideWhatToDoWithLine(const std::string& line, ReadingType& readingType,
		config::FutoInstanceConfig& futoInstanceConfig, std::vector<std::string>& initialStateStrings,
		bool& wasInitialStateParsed, std::vector<std::unique_ptr<csp::Constraint<int32_t>>>& constraintsVec) const;
	std::string prepareValueToStore(const std::string& s) const;
	void readInstanceSize(const std::string& line, config::FutoInstanceConfig& futoInstanceConfig) const;
	void readInitialStateLine(const std::string& line, std::vector<std::string>& initialStateStrings) const;
	void parseInitialState(std::vector<std::string>& initialStateStrings, config::FutoInstanceConfig& futoInstanceConfig) const;
	void readConstraint(const std::string& line, config::FutoInstanceConfig& futoInstanceConfig,
		std::vector<std::unique_ptr<csp::Constraint<int32_t>>>& constraintsVec) const;
};

} // namespace loader

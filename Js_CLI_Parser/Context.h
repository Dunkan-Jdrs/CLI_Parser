#pragma once
#include <vector>
#include <unordered_map>
#include <string>

class Subcommand;

using ValuesMap = std::unordered_map<std::string, std::vector<std::string>>;

class Context
{
public:
	const std::string& Get(const std::string& valueName) const;
	const std::vector<std::string>& GetAll(const std::string& valueName) const;
	
private:
	friend class ContextBuilder;

	// Must use std::move from ContextBuilder to avoid copy of unordered_map
	Context(ValuesMap&& valuesMap);

	ValuesMap m_values;
};


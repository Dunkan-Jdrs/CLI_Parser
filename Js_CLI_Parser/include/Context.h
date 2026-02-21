#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <charconv>

class Subcommand;

using ValuesMap = std::unordered_map<std::string, std::vector<std::string>>;

class Context
{
public:
	template<typename T>
	const T& Get(const std::string& valueName) const
	{
		T value;
		const std::string& rawValue = GetRaw(valueName);
		std::from_chars(rawValue.data(), rawValue.data() + rawValue.size(), value);

		return value;
	};

	const std::string& GetRaw(const std::string& valueName) const;
	const std::vector<std::string>& GetAll(const std::string& valueName) const;
	bool Has(const std::string& valueName) const;
	
private:
	friend class ContextBuilder;

	// Must use std::move from ContextBuilder to avoid copy of unordered_map
	Context(ValuesMap&& valuesMap);

	ValuesMap m_values;
};


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
	T Get(const std::string& valueName) const
	{
		T value{};
		const std::string& rawValue = GetRaw(valueName);
		std::from_chars(rawValue.data(), rawValue.data() + rawValue.size(), value);

		return value;
	};

	template<typename T>
	std::vector<T> GetAll(const std::string& valueName) const
	{
		const std::vector<std::string>& rawValues = GetAllRaw(valueName);
		std::vector<T> values(rawValues.size());
		for (int i = 0; i < rawValues.size(); ++i)
		{
			std::from_chars(rawValues[i].data(), rawValues[i].data() + rawValues[i].size(), values[i]);
		}
		

		return values;
	};

	const std::string& GetRaw(const std::string& valueName) const;
	const std::vector<std::string>& GetAllRaw(const std::string& valueName) const;
	bool Has(const std::string& valueName) const;
	
private:
	friend class ContextBuilder;

	// Must use std::move from ContextBuilder to avoid copy of unordered_map
	Context(ValuesMap&& valuesMap);

	ValuesMap m_values;
};


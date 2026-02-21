#include "Context.h"
#include <iostream>

Context::Context(ValuesMap&& values) : m_values(std::move(values))
{
}

const std::string& Context::GetRaw(const std::string& valueName) const
{
	if (!Has(valueName))
	{
		std::string message = "You can't get " + valueName + " because it doesn't exist";
		throw std::runtime_error(message);
	}

	const std::vector<std::string>& values = m_values.at(valueName);
	if (values.size() == 0)
	{
		std::string message = "You can't get " + valueName + " because it has been defined as a flag, without value";
		throw std::runtime_error(message);
	}

	return values[0];
}

const std::vector<std::string>& Context::GetAll(const std::string& valueName) const
{
	if (!Has(valueName))
	{
		std::string message = "You can't get " + valueName + " because it doesn't exist";
		throw std::runtime_error(message);
	}

	const std::vector<std::string>& values = m_values.at(valueName);
	if (values.size() == 0)
	{
		std::string message = "You can't get " + valueName + " because it has been defined as a flag, without value";
		throw std::runtime_error(message);
	}

	return values;
}

bool Context::Has(const std::string& valueName) const
{
	return m_values.find(valueName) != m_values.end();
}
 
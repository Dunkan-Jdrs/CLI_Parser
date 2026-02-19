#include "pch.h"
#include "Context.h"

Context::Context(ValuesMap&& values) : m_values(std::move(values))
{
}

const std::string& Context::Get(const std::string& valueName) const
{
	return m_values.at(valueName)[0];
}

const std::vector<std::string>& Context::GetAll(const std::string& valueName) const
{
	return m_values.at(valueName);
}

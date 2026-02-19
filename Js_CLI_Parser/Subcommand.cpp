#include "pch.h"

#include <iostream>

#include "Subcommand.h"
#include "Context.h"
#include "Token.h"

Subcommand::Subcommand(const std::string& name, std::function<void(const Context&)> callback)
{
	m_name = name;
	m_callback = callback;
}

void Subcommand::Exec(const Context& context)
{
	m_callback(context);
}

const std::string& Subcommand::GetName() const
{
	return m_name;
}

const Option& Subcommand::GetOption(const std::string& optionName) const
{
	int index = m_optionsMap.at(optionName);
	return m_options[index];
}

void Subcommand::Help() const
{
	std::cout << m_helpMessage << std::endl;
}

void Subcommand::AddOption(const Option& option)
{
	size_t index = m_options.size();

	m_options.push_back(option);

	m_optionsMap[option.GetLongName()] = index;
	m_optionsMap[option.GetShortName()] = index;
}

void Subcommand::AddOption(const std::string& shortName, const std::string& longName, const int arity)
{
	Option option = Option(shortName, longName, arity);
	AddOption(option);
}

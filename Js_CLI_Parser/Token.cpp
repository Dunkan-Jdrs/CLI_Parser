#include "pch.h"
#include "Token.h"
#include <stdexcept>

Token::Token(const std::string& name, const std::vector<std::string>& arguments)
{
	//TODO: Handle argument like -abc (-a, -b, -c)
	if (name[0] == '-') m_type = TokenType::Option;
	else m_type = TokenType::Subcommand;

	size_t firstChar = name.find_first_not_of('-');
	if (firstChar > 2)
	{
		throw std::runtime_error("A short option begin with a single -, and a long option with two -. There can't be more than two -");
	}
	if (firstChar == name.npos)
	{
		throw std::runtime_error("A '-' need to precede a command");
	}
	
	m_name = name.substr(firstChar);
	m_arguments = arguments;
}

const std::string& Token::GetName() const
{
	return m_name;
}

const std::vector<std::string>& Token::GetArguments() const
{
	return m_arguments;
}

TokenType Token::GetType() const
{
	return m_type;
}

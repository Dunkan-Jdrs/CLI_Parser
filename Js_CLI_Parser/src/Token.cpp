#include "Token.h"
#include <stdexcept>

Token::Token(const std::string& name, const std::vector<std::string>& arguments)
{
	if (name.empty() || name.find_first_not_of(' ') == name.npos)
	{
		throw std::runtime_error("Empty token found. Impossible case");
	}

	size_t firstChar = name.find_first_not_of('-');
	if (firstChar > 2)
	{
		throw std::runtime_error("A short option begin with a single -, and a long option with two -. There can't be more than two -");
	}
	if (firstChar == name.npos)
	{
		throw std::runtime_error("A '-' need to precede a command");
	}

	switch (firstChar)
	{
	case 0:
		m_type = TokenType::Subcommand;
		break;
	case 1:
		if (name.size() == 2) m_type = TokenType::ShortOption;
		else m_type = TokenType::ConcatOption;
		break;
	case 2:
		m_type = TokenType::LongOption;
		break;
	default:
		// Will never reach this because we thrown if firstChar > 2;
		m_type = TokenType::Undefined;
		return;
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

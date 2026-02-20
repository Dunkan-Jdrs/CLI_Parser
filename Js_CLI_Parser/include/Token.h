#pragma once
#include <string>
#include <vector>

enum class TokenType : char
{
	Subcommand,
	ShortOption,
	LongOption,
	ConcatOption,
	Undefined
};

class Token
{
public:
	Token(const std::string& name, const std::vector<std::string>& arguments);
	const std::string& GetName() const;
	const std::vector<std::string>& GetArguments() const;
	TokenType GetType() const;

private:
	TokenType m_type;
	std::string m_name;
	std::vector<std::string> m_arguments;
};


#include <stdexcept>

#include "ContextBuilder.h"
#include "Token.h"
#include "Subcommand.h"
#include "Option.h"

Context ContextBuilder::BuildContext(const Subcommand& subcommand, const std::vector<Token>& tokens)
{
	ValuesMap valuesMap = ValuesMap();

	for (const auto& token : tokens)
	{
		switch (token.GetType())
		{
		case TokenType::ShortOption:
			ConvertBasicOption(subcommand, token, valuesMap);
			break;

		case TokenType::LongOption:
			ConvertBasicOption(subcommand, token, valuesMap);
			break;

		case TokenType::ConcatOption:
			ConvertConcatOption(subcommand, token, valuesMap);
			break;

		default:
			break;
		}
	}

	return Context(std::move(valuesMap));
}

void ContextBuilder::ConvertBasicOption(const Subcommand& subcommand, const Token& token, ValuesMap& map)
{
	std::string tokenName = token.GetName();
	size_t argCount = token.GetArguments().size();

	Option option = subcommand.GetOption(tokenName);
	size_t optionArity = option.GetArity();

	if (argCount < optionArity)
	{
		std::string errorMessage = tokenName + " need " + std::to_string(optionArity) + " parameters";
		throw std::runtime_error(errorMessage);
	}

	if (argCount > option.GetArity())
	{
		std::string errorMessage = tokenName + " has too many parameters";
		throw std::runtime_error(errorMessage);
	}

	std::vector<std::string>& values = map[option.GetLongName()];

	for (size_t i = 0; i < argCount; ++i)
	{
		values.push_back(token.GetArguments()[i]);
	}
}

void ContextBuilder::ConvertConcatOption(const Subcommand& subcommand, const Token& token, ValuesMap& map)
{
	std::string tokenName = token.GetName();
	size_t concatNb = tokenName.size();

	for (size_t i = 0; i < concatNb - 1; ++i)
	{
		std::string currentOptionName = std::string(1, tokenName[i]);
		Option option = subcommand.GetOption(currentOptionName);

		if (option.GetArity() > 0)
		{
			std::string errorMessage = tokenName[i] + " require parameter. If you want to use it in concatened option, please use it as the end";
			throw std::runtime_error(errorMessage);
		}

		map[option.GetLongName()] = {};
	}

	Option option = subcommand.GetOption(std::string(1, tokenName[concatNb - 1]));
	size_t argCount = token.GetArguments().size();

	size_t optionArity = option.GetArity();

	if (argCount < optionArity)
	{
		std::string errorMessage = tokenName + " need " + std::to_string(optionArity) + " parameters";
		throw std::runtime_error(errorMessage);
	}

	if (argCount > option.GetArity())
	{
		std::string errorMessage = tokenName + " has too many parameters";
		throw std::runtime_error(errorMessage);
	}

	std::vector<std::string>& values = map[option.GetLongName()];

	for (int i = 0; i < argCount; ++i)
	{
		values.push_back(token.GetArguments()[i]);
	}
}
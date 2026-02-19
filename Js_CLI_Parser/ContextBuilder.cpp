#include "pch.h"

#include <stdexcept>

#include "ContextBuilder.h"
#include "Context.h"
#include "Token.h"
#include "Subcommand.h"
#include "Option.h"

Context ContextBuilder::BuildContext(const Subcommand& subcommand, const std::vector<Token>& tokens)
{
	ValuesMap valuesMap = ValuesMap();

	for (const auto& token : tokens)
	{
		if (token.GetType() == TokenType::Option)
		{
			std::string tokenName = token.GetName();
			size_t argCount = token.GetArguments().size();

			Option option = subcommand.GetOption(tokenName);

			if (argCount > option.GetArity())
			{
				std::string errorMessage = tokenName + " has too many parameters";
				throw std::runtime_error(errorMessage);
			}

			std::vector<std::string>& values = valuesMap[option.GetLongName()];

			for (int i = 0; i < argCount; ++i)
			{
				values.push_back(token.GetArguments()[i]);
			}
		}
	}

	return Context(std::move(valuesMap));
}

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Option.h"

class Context;

class Subcommand
{
public:
	Subcommand() = default;
	Subcommand(const std::string& name, std::function<void(const Context&)> callback);

	void Exec(const Context& context);

	void AddOption(const Option& option);

	const std::string& GetName() const;
	const Option& GetOption(const std::string& optionName) const;

private:
	bool HasRegisteredOption(const std::string& optionName) const;

	std::string m_name;
	std::function<void(const Context&)> m_callback;

	std::vector<Option> m_options;
	std::unordered_map<std::string, size_t> m_optionsMap;
};


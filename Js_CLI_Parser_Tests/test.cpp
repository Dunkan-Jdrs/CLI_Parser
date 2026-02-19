#include "pch.h"
#include "../Js_CLI_Parser/SubCommand.h"
#include "../Js_CLI_Parser/Context.h"
#include "../Js_CLI_Parser/App.h"
#include "../Js_CLI_Parser/Parser.h"

#pragma region PARSER
TEST(Parser, Parse_With_Subcommand_Only) {

	/*Init*/
	Parser parser = Parser();

	const std::string subcommandName = "log";
	const int argc = 2;
	const char* argv[argc] = { ".exe", subcommandName.c_str() };

	/*Execute*/
	std::vector<Token> tokens = parser.Parse(argc, argv);

	/*Verify*/
	EXPECT_EQ(tokens[0].GetName(), subcommandName);
	EXPECT_EQ(tokens[0].GetType(), TokenType::Subcommand);
}
#pragma endregion

#pragma region APP
TEST(App, Add_Subcommand_Twice)
{
	/*Init*/
	App app = App();
	Subcommand foo = Subcommand("Foo", nullptr);
	Subcommand fooBis = Subcommand("Foo", nullptr);

	/*Execute*/
	app.AddSubcommand(foo);

	/*Verify*/
	EXPECT_THROW(app.AddSubcommand(foo), std::runtime_error);
	EXPECT_THROW(app.AddSubcommand(fooBis), std::runtime_error);
}

TEST(App, App_Run_Subcommand_Only)
{
	/*Init*/
	App app = App();

	const std::string subcommandName = "Foo";
	const int argc = 2;
	const char* argv[argc] = { ".exe", subcommandName.c_str() };

	const int requiredValue = 10;
	int currentValue = 0;

	Subcommand foo = Subcommand(subcommandName, [requiredValue, &currentValue](const Context& ctx) {
		currentValue = requiredValue;
		});

	/*Execute*/
	app.AddSubcommand(foo);
	app.Run(argc, argv);

	/*Verify*/
	EXPECT_EQ(requiredValue, currentValue);
}

TEST(App, App_Run_Subcommand_With_Option)
{
	/*Init*/
	App app = App();

	const std::string subcommandName = "Foo";
	const std::string countOptionShortName = "c";
	const std::string countOptionLongName = "count";

	const int argc = 4;
	const char* argv[argc] = { ".exe", subcommandName.c_str(), "--count", "10" };

	const int requiredValue = 10;
	int currentValue = 0;

	Subcommand foo = Subcommand(subcommandName, [&currentValue, &countOptionLongName](const Context& ctx) {
		int count = std::stoi(ctx.Get(countOptionLongName));
		currentValue = count;
		});

	foo.AddOption(countOptionShortName, countOptionLongName, 1);
	app.AddSubcommand(foo);

	/*Execute*/

	app.Run(argc, argv);

	/*Verify*/
	EXPECT_EQ(requiredValue, currentValue);
}
#pragma endregion

#pragma region TOKEN
TEST(Token, Token_Type_Option)
{
	/*Init*/
	const std::string optionName = "-m";
	Token tokenOption = Token("-m", {});
	TokenType type;

	/*Execute*/
	type = tokenOption.GetType();

	/*Verify*/
	EXPECT_EQ(type, TokenType::Option);
}

TEST(Token, Token_Type_Subcommand)
{
	/*Init*/
	Token tokenOption = Token("m", {});
	TokenType type;

	/*Execute*/
	type = tokenOption.GetType();

	/*Verify*/
	EXPECT_EQ(type, TokenType::Subcommand);
}

TEST(Token, Token_Trim_Option_Name)
{
	/*Init*/
	Token tokenOption = Token("-m", {});

	/*Execute*/

	/*Verify*/
	EXPECT_TRUE(tokenOption.GetName()[0] != '-');
}

TEST(Token, Token_No_Name)
{
	/*Init*/

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(Token("---", {}), std::runtime_error);
}

TEST(Token, Token_Invalid_Name)
{
	/*Init*/

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(Token("---Test", {}), std::runtime_error);
}

TEST(Token, Token_Arguments_Stored)
{
	/*Init*/
	Token tokenOption = Token("-m", {"Hello", "Bonjour"});
	/*Execute*/

	/*Verify*/
	EXPECT_TRUE(tokenOption.GetArguments().size() == 2);
	EXPECT_TRUE(tokenOption.GetArguments()[0] == "Hello");
}
#pragma endregion

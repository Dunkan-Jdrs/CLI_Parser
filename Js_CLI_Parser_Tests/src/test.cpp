#include <gtest/gtest.h>
#include "Subcommand.h"
#include "ContextBuilder.h"
#include "App.h"
#include "Parser.h"

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

TEST(Parser, Parse_With_Flag_And_Option) {

	/*Init*/
	Parser parser = Parser();

	const std::string subcommandName = "subcommand";
	const std::string flagName = "--flag";
	const std::string optionName = "-o";

	const Option flag = Option("f", "flag", 0);
	const Option option = Option("o", "option", 1);

	const int argc = 5;
	const char* argv[argc] = { ".exe", subcommandName.c_str(), flagName.c_str(), optionName.c_str(), "foo"};

	/*Execute*/
	std::vector<Token> tokens = parser.Parse(argc, argv);

	/*Verify*/
	EXPECT_EQ(tokens[0].GetName(), subcommandName);
	EXPECT_EQ(tokens[0].GetType(), TokenType::Subcommand);
	EXPECT_EQ(tokens[0].GetArguments().size(), 0);

	EXPECT_EQ(tokens[1].GetName(), flagName.substr(2));
	EXPECT_EQ(tokens[1].GetType(), TokenType::LongOption);
	EXPECT_EQ(tokens[1].GetArguments().size(), 0);

	EXPECT_EQ(tokens[2].GetName(), optionName.substr(1));
	EXPECT_EQ(tokens[2].GetType(), TokenType::ShortOption);
	EXPECT_EQ(tokens[2].GetArguments().size(), 1);
}
#pragma endregion

#pragma region APP
TEST(App, App_Run_Nothing)
{
	/*Init*/
	App app = App();
	const int argc = 1;
	const char* argv[argc] = { ".exe" };

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(app.Run(argc, argv), std::runtime_error);
}

TEST(App, App_Run_Without_Subcommand)
{
	/*Init*/
	App app = App();
	const int argc = 2;
	const char* argv[argc] = { ".exe", "-v"};

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(app.Run(argc, argv), std::runtime_error);
}

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
		int count = std::stoi(ctx.GetRaw(countOptionLongName));
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
TEST(Token, Token_Type_ShortOption)
{
	/*Init*/
	const std::string optionName = "-m";
	Token tokenOption = Token(optionName, {});
	TokenType type;

	/*Execute*/
	type = tokenOption.GetType();

	/*Verify*/
	EXPECT_EQ(type, TokenType::ShortOption);
}

TEST(Token, Token_Type_ConcatOption)
{
	/*Init*/
	const std::string optionName = "-abc";
	Token tokenOption = Token(optionName, {});
	TokenType type;

	/*Execute*/
	type = tokenOption.GetType();

	/*Verify*/
	EXPECT_EQ(type, TokenType::ConcatOption);
}

TEST(Token, Token_Type_LongOption)
{
	/*Init*/
	const std::string optionName = "--message";
	Token tokenOption = Token(optionName, {});
	TokenType type;

	/*Execute*/
	type = tokenOption.GetType();

	/*Verify*/
	EXPECT_EQ(type, TokenType::LongOption);
}

TEST(Token, Token_Type_Subcommand)
{
	/*Init*/
	Token tokenOption = Token("subcommand", {});
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
	Token tokenOption = Token("-m", { "Hello", "Bonjour" });
	/*Execute*/

	/*Verify*/
	EXPECT_TRUE(tokenOption.GetArguments().size() == 2);
	EXPECT_TRUE(tokenOption.GetArguments()[0] == "Hello");
}
#pragma endregion

#pragma region Context
TEST(Context, Empty_Context)
{
	/*Init*/
	Subcommand subcommand = Subcommand("subcommand", [](const Context& _ctx) {
		std::string x = _ctx.GetRaw("x");
		});

	ContextBuilder builder = ContextBuilder();
	Context ctx = builder.BuildContext(subcommand, {});

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(subcommand.Exec(ctx), std::runtime_error);
}

TEST(Context, Context_With_Concat_Token)
{
	/*Init*/
	std::string concatFlag = "-abc";
	Token concatToken = Token(concatFlag, {});

	bool checkFlag = false;
	Subcommand subcommand = Subcommand("subcommand", [&checkFlag](const Context& _ctx) {
		checkFlag = _ctx.Has("a") && _ctx.Has("b") && _ctx.Has("c");
		});

	subcommand.AddOption(Option("a", "a", 0));
	subcommand.AddOption(Option("b", "b", 0));
	subcommand.AddOption(Option("c", "c", 0));

	ContextBuilder builder = ContextBuilder();
	Context ctx = builder.BuildContext(subcommand, { concatToken });

	/*Execute*/
	subcommand.Exec(ctx);

	/*Verify*/
	EXPECT_TRUE(checkFlag);
}

TEST(Context, Context_With_Concat_Token_With_Last_Option_Argument)
{
	/*Init*/
	const std::string arg = "foo";
	const std::string concatFlag = "-abc";
	Token concatToken = Token(concatFlag, { arg });

	bool checkFlag = false;
	Subcommand subcommand = Subcommand("subcommand", [&checkFlag, &arg](const Context& _ctx) {
		checkFlag = _ctx.Has("a") && _ctx.Has("b") && _ctx.Has("c") && _ctx.GetRaw("c") == arg;
		});

	subcommand.AddOption(Option("a", "a", 0));
	subcommand.AddOption(Option("b", "b", 0));
	subcommand.AddOption(Option("c", "c", 1));

	ContextBuilder builder = ContextBuilder();
	Context ctx = builder.BuildContext(subcommand, { concatToken });

	/*Execute*/
	subcommand.Exec(ctx);

	/*Verify*/
	EXPECT_TRUE(checkFlag);
}

TEST(Context, Context_With_Concat_Token_With_Middle_Option_Argument)
{
	/*Init*/
	const std::string arg = "foo";
	const std::string concatFlag = "-abc";
	Token concatToken = Token(concatFlag, { arg });

	bool checkFlag = false;
	Subcommand subcommand = Subcommand("subcommand", nullptr);
	subcommand.AddOption(Option("a", "a", 0));
	subcommand.AddOption(Option("b", "b", 1));
	subcommand.AddOption(Option("c", "c", 0));

	ContextBuilder builder = ContextBuilder();

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(builder.BuildContext(subcommand, { concatToken }), std::runtime_error);
}

TEST(Context, Context_Get_Empty_Arg)
{
	/*Init*/
	std::string flag = "-a";
	Token token = Token(flag, {});

	bool checkFlag = false;
	Subcommand subcommand = Subcommand("subcommand", [](const Context& _ctx) {
		std::string getA = _ctx.GetRaw("a");
		});

	subcommand.AddOption(Option("a", "a", 0));

	ContextBuilder builder = ContextBuilder();
	Context ctx = builder.BuildContext(subcommand, { token });

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(subcommand.Exec(ctx), std::runtime_error);
}

TEST(Context, Context_Get_All_Empty_Arg)
{
	/*Init*/
	std::string flag = "-a";
	Token token = Token(flag, {});

	bool checkFlag = false;
	Subcommand subcommand = Subcommand("subcommand", [](const Context& _ctx) {
		std::vector<std::string> getAllA = _ctx.GetAll("a");
		});

	subcommand.AddOption(Option("a", "a", 0));

	ContextBuilder builder = ContextBuilder();
	Context ctx = builder.BuildContext(subcommand, { token });

	/*Execute*/

	/*Verify*/
	EXPECT_THROW(subcommand.Exec(ctx), std::runtime_error);
}

TEST(Context, Context_Get_Typed_Arg)
{
	/*Init*/
	std::string flag = "--number";
	Token token = Token(flag, {"10"});

	bool checkFlag = false;
	int number = 0;
	Subcommand subcommand = Subcommand("subcommand", [&number](const Context& _ctx) {
		number = _ctx.Get<int>("number");
		});

	subcommand.AddOption(Option("n", "number", 1));

	ContextBuilder builder = ContextBuilder();
	Context ctx = builder.BuildContext(subcommand, { token });

	/*Execute*/
	subcommand.Exec(ctx);

	/*Verify*/
	EXPECT_EQ(number, 10);
}
#pragma endregion

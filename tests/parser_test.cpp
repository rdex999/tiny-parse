// Copyright (c) 2026 David Weizman
//
// Licensed under the MIT License. See LICENSE file in the project root.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include <gtest/gtest.h>
#include "tiny-parse/parser.hpp"

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

TEST(ParserDebug, Debug)
{
	tiny_parse::Parser parser;
	parser.add_option<int>("speed", "s", "The speed of the player.", 2);
	parser.add_option<double>("time", "t", "Run-time.", 1.5);
	parser.add_option<bool>("quiet", {}, "Quiet mode.");
	parser.add_option<std::string>("message", "m", "The message to display.");
	parser.add_option<std::string>("very-long-argument", {}, "A very long argument containing lots of text.");

	const char* argv[] {"./main", "--speed", "5", "--quiet"};

	tiny_parse::Result result = std::move(parser).parse(ARR_LEN(argv), argv);
}

TEST(ParserParsingTest, ParseCorrectly)
{
	const char* argv[] = { "./main", "--quiet", "-m", "Hello world!", "--speed", "50", "--time", "60.3" };

	tiny_parse::Result result = tiny_parse::Parser()
		.add_option<int>("speed", "s", "The speed of the player.", 2)
		.add_option<double>("time", "t", "Run-time.", 1.5)
		.add_option<bool>("quiet", {}, "Quiet mode.")
		.add_option<std::string>("message", "m", "The message to display.")
		.parse(ARR_LEN(argv), argv);

	ASSERT_EQ(result.result, tiny_parse::ResultType::SUCCESS);
	ASSERT_EQ(result.get<int>("speed"), 50);
	ASSERT_EQ(result.get<double>("time"), 60.3);
	ASSERT_EQ(result.get<bool>("quiet"), true);
	ASSERT_EQ(result.get<std::string>("m"), "Hello world!");
}

TEST(ParserDuplicateOptionTest, Throws)
{
	bool threw = false;
	try
	{
		tiny_parse::Parser parser;
		parser.add_option<int>("speed", "s", "The speed of the player.", 2);
		parser.add_option<int>("speed", "s", "The speed of the player.", 2);
	}
	catch (const std::logic_error&)
	{
		threw = true;
	}

	ASSERT_TRUE(threw);
}

TEST(ParserMissingArgumentTest, ResultFailureWithError)
{
	const char* argv[] = { "./main", "--speed", "50" };
	const tiny_parse::Result result = tiny_parse::Parser()
		.add_option<int>("speed", "s", "The speed of the player.", 2)
		.add_option<double>("time", "t", "Run-time.")
		.add_option<std::string>("name", {}, "The name of the player.")
		.parse(ARR_LEN(argv), argv, true, false);

	ASSERT_EQ(result.result, tiny_parse::ResultType::FAILURE);
	ASSERT_EQ(result.error, "Missing arguments: --time, --name");
}

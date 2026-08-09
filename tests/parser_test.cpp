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

TEST(ParserAddOptionTest, DoesntThrow)
{
	tiny_parse::Parser parser;
	parser.add_option<int>("speed", "s", "The speed of the player.", 2);
	parser.add_option<double>("time", "t", "Run-time.", 1.5);
	parser.add_option<bool>("quiet", {}, "Quiet mode.");
	parser.add_option<std::string>("message", "m", "The message to display.");
	parser.add_option<std::string>("format", "f", "The format to use.");

	const char* argv[] {"./main", "--speed"};

	tiny_parse::Result result = std::move(parser).parse(1, argv);
	std::cout << result.full_message() << std::endl;
}

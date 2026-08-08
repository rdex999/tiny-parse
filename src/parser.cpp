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

#include <utility>

#include "tiny-parse/parser.hpp"

namespace tiny_parse
{
Result Parser::parse(int argc, char* argv[], bool help, bool address_error) &&
{
	if (argv == nullptr)
		throw std::invalid_argument("Argument array (argv) cannot be null.");

	/* TODO: Implement parsing. */

	return {std::move(options_map_), std::move(options_), ResultType::SUCCESS, {}, {}, {}};
}

template<typename T>
void Parser::add_option(std::string canonical, std::string alias, std::string help, std::optional<T> default_value)
{
	if (options_map_.contains(canonical))
		throw std::logic_error(std::string("Argument \"") + canonical + "\" was already defined.");

	std::unique_ptr<Option> option = std::make_unique<Option>(canonical, std::move(default_value.value_or(T {})),
		!default_value.has_value(), std::move(alias), std::move(help));

	options_map_[canonical] = option.get();
	if (!alias.empty())
		options_map_[alias] = option.get();

	options_.push_back(std::move(option));
}
}

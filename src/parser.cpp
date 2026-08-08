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
Result Parser::parse(int argc, const char* argv[], bool help, bool address_error) &&
{
	if (argv == nullptr)
		throw std::invalid_argument("Argument array (argv) cannot be null.");

	argc_ = argc;
	argv_ = argv;

	while (can_consume())
	{
		const char* flag = consume();
		if (is_short_flag(flag))
		{
			/* TODO: Parse long argument. */
		}
		else if (is_short_flag(flag))
		{
			/* TODO: Parse short argument. */
		}
		else
		{
			/* TODO: Error. */
		}
	}

	/* TODO: Confirm that all required arguments are present. */

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

[[nodiscard]] inline const char* Parser::consume()
{
	if (argv_[position_] == nullptr)
		throw std::invalid_argument(std::string("String ") + std::to_string(position_) + " in argv is null.");

	return argv_[position_++];
}

[[nodiscard]] inline const char* Parser::peek(int offset) const
{
	if (argv_[position_ + offset] == nullptr)
		throw std::invalid_argument(std::string("String ") + std::to_string(position_ + offset) + " in argv is null.");

	return argv_[position_ + offset];
}

[[nodiscard]] inline bool Parser::can_consume() const { return position_ < argc_; }

[[nodiscard]] inline bool Parser::is_short_flag(const char* flag) { return flag[0] == '-' && isalpha(flag[1]); }
[[nodiscard]] inline bool Parser::is_long_flag(const char* flag) { return flag[0] == '-' && flag[1] == '-' && isalpha(flag[2]); }
}

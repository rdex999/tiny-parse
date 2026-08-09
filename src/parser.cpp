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

#include <format>

namespace tiny_parse
{
Result Parser::parse(int argc, const char* argv[], bool help, bool address_error) &&
{
	if (argv == nullptr)
		throw std::invalid_argument("Argument array (argv) cannot be null.");

	if (argc < 1)
		throw std::invalid_argument(std::string("Argument count (argc) cannot be less than 1. Given was ") + std::to_string(argc) + ".");

	argc_ = argc;
	argv_ = argv;

	std::string help_msg = build_help();
	std::string usage_msg = build_usage();
	std::string error_msg;

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

	return {std::move(options_map_), std::move(options_), ResultType::SUCCESS, std::move(help_msg), std::move(usage_msg), std::move(error_msg)};
}

template<typename T>
void Parser::add_option(const std::string& canonical, const std::string& alias, std::string help, const std::optional<T>& default_value)
{
	if (options_map_.contains(canonical))
		throw std::logic_error(std::string("Argument \"") + canonical + "\" was already defined.");

	if (std::is_same_v<T, bool> && default_value.has_value())
		throw std::invalid_argument("Boolean argument cannot have a default value. Default is always false.");

	const bool required = !default_value.has_value() && !std::is_same_v<T, bool>;
	std::unique_ptr<Option> option = std::make_unique<Option>(canonical, std::move(default_value.value_or(T {})),
		required, alias, std::move(help));

	options_map_[canonical] = option.get();
	if (!alias.empty())
		options_map_[alias] = option.get();

	options_.push_back(std::move(option));
}
template void Parser::add_option<int>(const std::string& canonical, const std::string& alias, std::string help, const std::optional<int>& default_value);
template void Parser::add_option<double>(const std::string& canonical, const std::string& alias, std::string help, const std::optional<double>& default_value);
template void Parser::add_option<bool>(const std::string& canonical, const std::string& alias, std::string help, const std::optional<bool>& default_value);
template void Parser::add_option<std::string>(const std::string& canonical, const std::string& alias, std::string help, const std::optional<std::string>& default_value);

inline std::string Parser::build_help() const
{
	std::string msg = "Options:\n\t";
	for (const auto& option : options_)
	{
		std::string opt;

		opt += std::format("--{}", option->canonical);
		if (!option->alias.empty())
		{
			if (const int padding = 10 - static_cast<int>(opt.length()); padding > 0)
				opt += std::string(padding, ' ');

			opt += std::format(" | -{}", option->alias);
		}

		if (const int padding = 17 - static_cast<int>(opt.length()); padding > 0)
			opt += std::string(padding, ' ');

		opt += std::format(" <=> [{}] ", option->type_string());
		if (!option->help.empty())
			opt += option->help;

		if (!opt.ends_with(' '))
			opt += ' ';

		if (!option->required && option->type_index() != Option::bool_index)
			opt += std::format("Default {}.", option->value_string());

		msg += opt + "\n\t";
	}

	return msg;
}

inline std::string Parser::build_usage() const
{
	const char* executable = argv_[0];
	if (executable == nullptr)
		throw std::invalid_argument("String 0 in argv, the executable name, is null. Please see a doctor.");

	std::string result = std::format("Usage: {}", executable);
	for (const auto& option : options_)
	{
		if (!option->required)
			continue;

		std::string upper = option->canonical;
		std::ranges::transform(upper, upper.begin(), ::toupper);

		result += std::format(" --{} <{}>", option->canonical, upper);
	}

	return result;
}

inline const char* Parser::consume()
{
	if (argv_[position_] == nullptr)
		throw std::invalid_argument(std::string("String ") + std::to_string(position_) + " in argv is null.");

	return argv_[position_++];
}

inline const char* Parser::peek(int offset) const
{
	if (argv_[position_ + offset] == nullptr)
		throw std::invalid_argument(std::string("String ") + std::to_string(position_ + offset) + " in argv is null.");

	return argv_[position_ + offset];
}

inline bool Parser::can_consume() const				{ return position_ < argc_; }
inline bool Parser::is_short_flag(const char* flag) { return flag[0] == '-' && isalpha(flag[1]); }
inline bool Parser::is_long_flag(const char* flag)	{ return flag[0] == '-' && flag[1] == '-' && isalpha(flag[2]); }
}

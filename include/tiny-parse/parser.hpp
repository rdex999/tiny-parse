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

#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "result.hpp"
#include "../../src/option.hpp"

namespace tiny_parse
{
class Parser
{
public:
	/**
	 * Parses the command line arguments. Results are passed in the result pointer.
	 * @param argc The amount of arguments in argv.
	 * @param argv An array of C-style strings, contains argc elements.
	 * @param help Whether to add a --help/-h argument and print help information if specified.
	 * @param address_error Whether to print errors and correct usage examples on parsing failure.
	 */
	Result parse(int argc, const char* argv[], bool help = true, bool address_error = true) &&;

	/**
	 * Adds the given argument. Will be parsed when parse() is called.
	 * @tparam T The type of the argument.
	 * @param canonical Optional. The full name of the argument, not including leading "--". For example, "speed" (not "--speed")
	 * @param alias Optional. The short name of the argument, not including leading "-". For example, "s" (not "-s")
	 * @param help Optional. Help message describing the purpose of the argument.
	 * @param default_value Optional. If no value is given, the parameter is treated as required.
	 * If a value is given, the argument is treated as optional and the default value is used if no value was passed.
	 */
	template<typename  T>
	void add_option(const std::string& canonical, const std::string& alias = {}, std::string help = {}, const std::optional<T>& default_value = std::nullopt);

private:
	std::unordered_map<std::string, Option*> options_map_;
	std::vector<std::unique_ptr<Option>> options_;

	int argc_ = -1;
	const char** argv_ = nullptr;
	uint position_ = 1;

	[[nodiscard]] Option* try_get(const std::string& name);

	[[nodiscard]] inline std::string build_help() const;
	[[nodiscard]] inline std::string build_usage() const;

	[[nodiscard]] inline const char* consume();
	[[nodiscard]] inline const char* peek(int offset) const;
	[[nodiscard]] inline bool can_consume() const;
	[[nodiscard]] static inline bool is_short_flag(const char* flag);
	[[nodiscard]] static inline bool is_long_flag(const char* flag);
	[[nodiscard]] static inline bool is_flag(const char* flag);

	[[nodiscard]] static inline std::optional<int> try_parse_int(const std::string& str);
};
}

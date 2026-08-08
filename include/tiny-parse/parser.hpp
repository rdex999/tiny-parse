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

#include "../../src/option.hpp"

namespace tiny_parse
{
class Parser
{
public:
	Parser();

	void parse(int argc, char* argv[]);

	/**
	 *
	 * @tparam T The type of the argument.
	 * @param canonical Optional. The full name of the argument, not including leading "--". For example, "speed" (not "--speed")
	 * @param alias Optional. The short name of the argument, not including leading "-". For example, "s" (not "-s")
	 * @param help Optional. Help message describing the purpose of the argument.
	 * @param default_value Optional. If no value is given, the parameter is treated as required.
	 * If a value is given, the argument is treated as optional and the default value is used if no value was passed.
	 */
	template<typename  T>
	void add_option(std::string canonical, std::string alias = {}, std::string help = {}, std::optional<T> default_value = std::nullopt);

	template<typename T>
	T get(const std::string& name);

private:
	std::unordered_map<std::string, Option&> options_by_name_;
	std::vector<Option> options_;
};
}

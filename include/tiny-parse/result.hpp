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

#include <unordered_map>
#include <vector>

#include "../../src/option.hpp"

namespace tiny_parse
{
enum class ResultType : uint8_t
{
	SUCCESS,
	FAILURE,
	HELP,
};

class Result
{
public:
	Result(std::unordered_map<std::string, Option*>&& options_map, std::vector<std::unique_ptr<Option>>&& options, ResultType result, std::string help, std::string usage, std::string error)
		: result(result), help(std::move(help)), usage(std::move(usage)), error(std::move(error)), options_map_(std::move(options_map)), options_(std::move(options))
	{}

	const ResultType result;
	const std::string help;
	const std::string usage;
	const std::string error;

	/**
	 * A message to the user based on the result of the parsing. If parsing has failed, includes the error, and correct usage example.
	 * @return The generated message
	 */
	[[nodiscard]] std::string message() const;

	/**
	 * A full help message with a correct usage example.
	 * @return The generated help message and correct usage.
	 */
	[[nodiscard]] std::string full_message() const { return usage + '\n' + help; }

	/**
	 * Gets the requested argument by its canonical or alias name.
	 * @tparam T The type of the argument to get.
	 * @param canonical The canonical (long name) of the argument.
	 * @return T as the requested argument.
	 */
	template<typename T>
	[[nodiscard]] T get(const std::string& canonical);

private:
	std::unordered_map<std::string, Option*> options_map_;
	std::vector<std::unique_ptr<Option>> options_;
};
}

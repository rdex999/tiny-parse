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
class Parser;

enum class ResultType : uint8_t
{
	/** Parsing was successful, arguments can be used freely. */
	SUCCESS,

	/** An error has occurred, arguments should not be used. The error message available in the returned Result object. */
	FAILURE,

	/**
	 * The --help/-h flags were used and a help message was printed.
	 * Not all arguments are guaranteed to be present, and should not be used.
	 * @note Can only be set if the help argument in Parser::parse() was set to true.
	 */
	HELP,
};

/**
 * Describes the result of the parsing operation, and gives access to the parsed arguments.
 * @note Created by the Parser::parse() method.
 */
class Result
{
public:
	/**
	 * The result status of the parsing operation. Always check before accessing arguments.
	 */
	const ResultType result;

	/**
	 * The generated help message. Available regardless of the result of the parsing operation.
	 */
	const std::string help;

	/**
	 * The generated usage message. Available regardless of the result of the parsing operation.
	 */
	const std::string usage;

	/**
	 * The error message. If no errors were found, its an empty string.
	 * Always contains an error when result is ResultType::FAILURE, and might contain an error (but should be ignored)
	 * when result is ResultType::HELP
	 */
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
	 * @param canonical The canonical or alias name of the argument.
	 * @return T as the requested argument.
	 */
	template<typename T>
	[[nodiscard]] T get(const std::string& canonical);

private:
	friend class tiny_parse::Parser;

	Result(std::unordered_map<std::string, Option*>&& options_map, std::vector<std::unique_ptr<Option>>&& options, ResultType result, std::string help, std::string usage, std::string error)
	: result(result), help(std::move(help)), usage(std::move(usage)), error(std::move(error)), options_map_(std::move(options_map)), options_(std::move(options))
	{}

	std::unordered_map<std::string, Option*> options_map_;
	std::vector<std::unique_ptr<Option>> options_;
};
}

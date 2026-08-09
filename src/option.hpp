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

#include <string>
#include <variant>
#include <sys/types.h>

#include "utils.hpp"

namespace tiny_parse
{
enum class OptionType : uint8_t
{
	INT,
	DOUBLE,
	BOOL,
	STRING,
};

class Option
{
public:
	template <typename T>
	explicit Option(std::string canonical, T value, bool required, std::string alias = {}, std::string help = {})
	: canonical(std::move(canonical)), alias(std::move(alias)), help(std::move(help)), required(required),
		value_(value)
	{
		assert_supported_type<T>();
	}

	const std::string canonical;
	const std::string alias;
	const std::string help;
	const bool required;

	template <typename T>
	void set(T value);
	template <typename T>
	[[nodiscard]] T get() const;
	[[nodiscard]] bool was_set() const { return set_count > 0; };
	[[nodiscard]] OptionType type() const { return static_cast<OptionType>(type_index());}
	[[nodiscard]] std::string type_string() const;
	[[nodiscard]] std::string value_string() const;

private:
	static constexpr int int_index		= 0;
	static constexpr int double_index	= 1;
	static constexpr int bool_index		= 2;
	static constexpr int string_index	= 3;

	std::variant<int, double, bool, std::string> value_;
	uint set_count = 0;

	[[nodiscard]] int type_index() const;
};
}

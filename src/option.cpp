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

#include "option.hpp"

#include <format>

namespace tiny_parse
{
template<typename T>
void Option::set(T value)
{
	assert_supported_type<T>();
	value_ = value;
	++set_count;
}
template void Option::set<int>(int value);
template void Option::set<double>(double value);
template void Option::set<bool>(bool value);
template void Option::set<std::string>(std::string value);

template<typename T>
T Option::get() const
{
	assert_supported_type<T>();
	if (!std::holds_alternative<T>(value_))
		throw std::logic_error("The option does not contain the requested type.");

	return std::get<T>(value_);
}

std::string Option::type_string() const
{
	switch (value_.index())
	{
	case int_index:		return "int";
	case double_index:	return "double";
	case bool_index:	return "bool";
	case string_index:	return "string";

	default:
		throw std::logic_error(std::format("Option::type() called when value_ was not set. Index {}.", value_.index()));
	}
}

int Option::type_index() const { return static_cast<int>(value_.index()); }

std::string Option::value_string() const
{
	return std::visit([]<typename T>(const T& value) -> std::string
	{
		if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>)
			return std::to_string(value);

		else if constexpr (std::is_same_v<T, bool>)
			return value ? "true" : "false";

		else if constexpr (std::is_same_v<T, std::string>)
			return std::format("\"{}\"", value);

		else
			throw std::logic_error("Option::value_string() called when value_ was not set.");

	}, value_);
}
}

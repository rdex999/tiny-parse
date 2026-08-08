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

#include <optional>

#include "utils.hpp"

namespace tiny_parse
{
template <typename T>
Option::Option(std::string canonical, T value, bool required, std::string alias, std::string help)
	: canonical(std::move(canonical)), alias(std::move(alias)), help(std::move(help)), required(required),
		value_(value)
{
	assert_supported_type<T>();
}

template<typename T>
void Option::set(T value)
{
	assert_supported_type<T>();
	value_ = value;
	++set_count;
}

template<typename T>
T Option::get() const
{
	assert_supported_type<T>();
	if (!std::holds_alternative<T>(value_))
		throw std::logic_error("The option does not contain the requested type.");

	return std::get<T>(value_);
}
}

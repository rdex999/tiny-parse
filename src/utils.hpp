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
#include <type_traits>

namespace tiny_parse
{
template <typename T>
constexpr bool is_supported_type()
{
	return std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, bool> || std::is_same_v<T, std::string>;
}

template <typename T>
constexpr void assert_supported_type()
{
	static_assert(is_supported_type<T>(), "Type T must be a supported type. The supported types are: int, double, bool, std::string.");
}
}

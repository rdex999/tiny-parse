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

#include "tiny-parse/result.hpp"

namespace tiny_parse
{
[[nodiscard]] std::string Result::message() const
{
	if (result == ResultType::SUCCESS)
		return {};

	return error + '\n' + std::string("Correct usage: ") + usage;
}

template<typename T>
T Result::get(const std::string& canonical)
{
	if (!options_map_.contains(canonical))
		throw std::logic_error(std::string("Argument \"") + canonical + "\" was not defined.");

	return options_map_[canonical]->get<T>();
}
}

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

#include <format>

namespace tiny_parse
{
std::string Result::message() const
{
	if (result == ResultType::SUCCESS)
		return {};

	return std::format("Error: {}\n{}", error, usage);
}

std::string Result::full_message() const
{
	if (description.empty())
		return usage + '\n' + help;

	return description + '\n' + usage + '\n' + help;
}

template<typename T>
T Result::get(const std::string& name)
{
	if (options_map_.contains(name))
		return options_map_[name]->get<T>();

	if (alias_map_.contains(name))
		return alias_map_[name]->get<T>();

	throw std::logic_error(std::string("Argument \"") + name + "\" was not defined.");
}

template int Result::get<int>(const std::string& name);
template double Result::get<double>(const std::string& name);
template bool Result::get<bool>(const std::string& name);
template std::string Result::get<std::string>(const std::string& name);
}

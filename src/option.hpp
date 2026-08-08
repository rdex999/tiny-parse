// Copyright 2026 David Weizman
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>
#include <variant>

namespace tiny_parse
{
class Option
{
public:
	std::variant<int, double, bool, std::string> value;
	const std::string canonical;
	const std::string alias;
	const std::string help;
	const bool required;
};
}

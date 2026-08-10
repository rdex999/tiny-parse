# Tiny Parse
Tiny Parse is a fast, lightweight C++ command-line argument parsing library.

# Argument Syntax
Supported types are: int, double, bool, string.  
__int__		- `--speed <INTEGER>` `--speed 5`  
__double__ 	- `--speed <FRACTION>` `--speed 1.2` `--speed 1`  
__bool__ 	- `--quiet`  
__string__ 	- `--message <TEXT>` `--message Hello`  
  
Flag syntax can be either by full argument name, ("--" prefix) or by alias. ("-" prefix)  
For example: `--speed`, or alias: `-s`

# Documentation
Use Doxygen with the present Doxyfile to generate documentation: `doxygen Doxyfile`  
This fill generate documentation in the `docs` folder.  
If your lazy, just read the comments in the public headers, (`include/tiny-parse/`)
There's really not much to document.

# Usage
## Configuration
If your using Cmake - it's as simple as adding the repo as a 
git-submodule, and adding `add_subdirectory(<PATH>)` to 
Your `CMakeLists.txt`.  
If you're not using Cmake, well… build the library with Cmake,
take the public headers from `include/tiny-parse` and use em,
then link your program against the compiled library binary?
(Exploration is good for your health)

## Basic Usage
Though you can see the full documentation, the library is too simple for that.  
You use the tiny_parse::Parser class for declaring arguments, and then parsing them.
Parsing returns a tiny_parse::Result object, that specifies the result and 
gives access to the parsed arguments.  
If you don't want to install Doxygen or your just lazy, just read the comments in 
`include/tiny-parse/parser.hpp` and 
`include/tiny-parse/result.hpp`, and you'll understand everything.
### Example
```c++
#include <iostream>
#include "tiny-parse/parser.hpp"
#include "tiny-parse/result.hpp"

int main(int argc, char* argv[])
{
	tiny_parse::Result result = tiny_parse::Parser()
		.add_option<int>("speed", "s", "The speed of the player.", 2)
		.add_option<double>("time", "t", "Run-time.", 1.5)
		.add_option<bool>("quiet", {}, "Quiet mode.")
		.add_option<std::string>("message", "m", "The message to display.")
		.parse(argc, argv);
   
	if (result.result == tiny_parse::ResultType::FAILURE)
		return 1;	/* The error and generated usage message were already printed. (in stderr) */
    
	if (result.result == tiny_parse::ResultType::HELP)
		return 0;	/* The generated help&usage messages were already printed. */
    
	std::cout << "--speed: " << result.get<int>("speed") << std::endl;
	std::cout << "--time: " << result.get<double>("time") << std::endl;
	std::cout << "--quiet: " << result.get<bool>("quiet") << std::endl;
	std::cout << "--message: " << result.get<std::string>("message") << std::endl;
    
	return 0;
}
```

Pretty much self-explanatory, but let's go over this example:  
__add_option()__ Takes in: canonical name, alias (optional), help message (optional), default value (optional).
If you do not supply a default value, the argument is treated as required, and not optional.  
  
__parse()__ Takes in: guess what.  
But it returns a Result object. Which, contains, well your parsed arguments.
As well as generated help&usage messages, and an error message if any errors have occurred.  
Usage is really self-explanatory, but its worth noting that you can
also access parsed arguments by their alias name. That could be, in the example above,
like so:
```c++
result.get<int>("s");	// instead of "speed"
```
That being said, note that in the example above:
 - The __speed__ and __time__ arguments are optional, because 
a default value was provided for them.
 - The __message__ argument is not optional and must be provided, because no default value was specified. (__quiet__ is a boolean, hence it's not required nor optional)
 - The __quiet__ argument does not have an alias name. (like "-q")
 - You really should follow my GitHub account.


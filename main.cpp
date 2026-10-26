// cli interface — does
// file_manager — does file checks, reads, writes
// parser
// scope_separator — separates expressions into main scope, functions, templates, enums, structures
// 		Function hoisting
// structures_decoder
// undefined_behavior_checker

#include "source/cli_interface/cli_interface.hpp"
#include <iostream>


int main(int argc, char* argv[]) {
	std::variant<command_result_types, process_data_type> cli_result = cli_interface(argc, argv);

	// If result from cli_interface is a command_result_type then
	if (auto result_command = std::get_if<command_result_types>(&cli_result)) {
		switch (*result_command) {
			case command_result_types::help:
				std::cout << "Scpp commands:\n\t-h || --help — to see list of commands\n\t-v || --version — to see the program's version" << '\n';
				return 0;
			case command_result_types::version:
				std::cout << "Scpp version 0.0.1" << '\n';
				return 0;
			case command_result_types::wrong_command:
				std::cout << "Wrong command" << '\n';
				return -1;
		}
	}


	// If code reached this place then cli_result is a process_data_type
	process_data_type process_data = std::get<process_data_type>(cli_result);



	return 0;
}

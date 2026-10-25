#include "cli_interface.hpp"

std::variant<command_result_types, process_data_type> cli_interface(int argc, char* argv[]) {
	if (argc == 1) {
		// No arguments so does --help command
		return command_result_types::help;
	}

	if (argc == 2) {
		// 1 argument that is either `version` or `help` flag or a file name
		std::string token = argv[1];

		if (token[0] != '-') {
			// It is a file
			return process_data_type{.input_file_name = token};
		}

		// it is a flag
		if (token == "-h" || token == "--help") {
			return command_result_types::help;
		} else if (token == "-v" || token == "--version") {
			return command_result_types::version;
		} else {
			return command_result_types::wrong_command;
		}
	}

	// It has more than 1 argument so we check by flags
	process_data_type process_data;

	int skip = -1;
	for (int i = 0; i < argc; ++i) {
		if (i == skip) continue;

		std::string token = argv[i];

		if (token == "-o") {
			// Check if next token exists by comparing id of next token (i+1) to arguments count (argc)
			if (i+1 > argc) {
				// If it is bigger then throw error

			}
			// Make so next value is not iterated by the loop
			skip = i + 1;

			process_data.output_file_name = argv[i+1];
		} else if (token == "-b") {
			process_data.file_actions = file_action_types::build;
		} else if (token == "-r") {
			process_data.file_actions = file_action_types::run;
		}
	}

	return process_data;
}

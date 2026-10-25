#include <string>
#include <variant>

#define DEFAULT_PROCESS file_action_types::transpile
#define DEFAULT_NAME "a.cpp"

enum class command_result_types {
	version,
	help,
	wrong_command
};

enum class file_action_types {
	// Transpile scpp to cpp
	transpile,
	// Transpile scpp to cpp and make source file
	build,
	// Transpile scpp to cpp, make source file and run source file
	run
};

struct process_data_type {
	std::string input_file_name;
	std::string output_file_name = DEFAULT_NAME;
	file_action_types file_actions = {DEFAULT_PROCESS};
	std::string output_source_file_name;
};

std::variant<command_result_types, process_data_type> cli_interface(int argc, char* argv[]);

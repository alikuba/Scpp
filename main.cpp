// cli interface — does
// file_manager — does file checks, reads, writes
// parser
// scope_separator — separates expressions into main scope, functions, templates, enums, structures
// 		Function hoisting
// structures_decoder
// undefined_behavior_checker

#include "source/cli_interface/cli_interface.hpp"


int main(int argc, char* argv[]) {
	cli_interface(argc, argv);

	return 0;
}

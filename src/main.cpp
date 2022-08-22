#include "Scenario.h"
#include "YamlParseError.h"
#include "tps/quick_arg_parser.hpp"
#include <yaml-cpp/yaml.h>


using namespace scp;

struct Args : public MainArguments<Args> {
	using MainArguments<Args>::MainArguments;
	std::string input_file = option("input-file", 'i', "The input yaml file with the scenario to parse");
};

int main(int argc, char** argv) {
	Args args{ argc, argv };

	if (!args.input_file.empty()) {
		std::cout << "Consuming input file: " << args.input_file << std::endl;
		try {
			Scenario scenario{ YAML::LoadFile(args.input_file) };
			auto totalTime = scenario.computeScenarioTime();
		}
		catch (const YamlParseError& error) {
			std::cout << "Yaml Error: " << error.what() << std::endl;
		}
	}
	else {
		std::cout << "no input file provided, use: '--input-file {file_path}`" << std::endl;
	}

	return 0;
}
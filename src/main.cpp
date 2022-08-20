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

	try {
		Scenario scenario{ YAML::LoadFile(args.input_file) };
		auto totalTime = scenario.computeScenarioTime();
		std::cout << "Total time to complete the scenario in listed input file {" << args.input_file << "}: " << totalTime;
	}
	catch (const YamlParseError& error) {
		std::cout << "Yaml Error: " << error.what() << std::endl;
	}

	return 0;
}
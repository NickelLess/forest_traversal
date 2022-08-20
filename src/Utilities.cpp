#include "Utilities.h"
#include "YamlParseError.h"

#include <yaml-cpp/yaml.h>
#include <sstream>

namespace scp {

void validateScenario(const YAML::Node& scenario) {
	if (!scenario["scenario"]) {
		throw YamlParseError("'scenario' not included in provided scenario input");
	}

	if (!scenario["scenario"].IsSequence()) {
		throw YamlParseError("'scenario' is not a sequence. 'scenario' needs to be a sequence of bridges");
	}
}

void validateBridge(const YAML::Node& bridge) {
	if (!bridge["bridge"]) {
		throw YamlParseError("'bridge' not included in provided bridge input");
	}

	auto element = bridge["bridge"];
	if (!element["length"]) {
		throw YamlParseError("'length' not included in provided bridge element");
	}

	// It may be the case where no new hikers are brought in
	if (element["hikers"]) {
		if (!element["hikers"].IsSequence()) {
			throw YamlParseError("'hikers' is not a sequence. 'hikers' needs to be a sequence of speeds");
		}
	}
}

int parseBridgeLength(const YAML::Node& bridge) {
	int length;
	std::string units;
	std::stringstream ss(bridge["length"].as<std::string>());
	ss >> length >> units;
	return length;
}

int parseHikerSpeed(const YAML::Node& hiker) {
	int length;
	std::string units;
	std::stringstream ss(hiker.as<std::string>());
	ss >> length >> units;
	return length;
}

} // namespace scp
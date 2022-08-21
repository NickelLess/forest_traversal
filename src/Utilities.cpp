#include "Utilities.h"
#include "YamlParseError.h"

#include <yaml-cpp/yaml.h>
#include <sstream>
#include <iostream>

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

double parseBridgeLength(const YAML::Node& lengthYaml) {
	double length;
	std::string units;
	std::stringstream ss(lengthYaml.as<std::string>());
	ss >> length >> units;

	if (length < 0) {
		throw YamlParseError("bridge length {" + std::to_string(length) + "} must be >= 0");
	}
	return length;
}

double parseHikerSpeed(const YAML::Node& hikerYaml) {
	double speed;
	std::string units;
	std::stringstream ss(hikerYaml.as<std::string>());
	ss >> speed >> units;

	if (speed <= 0) {
		throw YamlParseError("hiker speed {" + std::to_string(speed) + "} must be > 0");
	}
	return speed;
}

} // namespace scp
#include "Scenario.h"
#include "Utilities.h"

#include <yaml-cpp/yaml.h>
#include <set>
#include <iostream>

namespace scp {

Scenario::Scenario(const YAML::Node& scenario) {
	validateScenario(scenario);

	std::multiset<double> hikerSpeeds;
	for (std::size_t i = 0; i < scenario["scenario"].size(); ++i) {
		auto bridgeYaml = scenario["scenario"][i];
		validateBridge(bridgeYaml);
		for (std::size_t j = 0; j < bridgeYaml["bridge"]["hikers"].size(); ++j) {
			hikerSpeeds.insert(parseHikerSpeed(bridgeYaml["bridge"]["hikers"][j]));
		}
		m_bridges.emplace_back(hikerSpeeds, parseBridgeLength(bridgeYaml["bridge"]["length"]));
		std::cout << bridgeYaml << std::endl;
	}
	std::cout << "SCENARIO CONSTRUCTED" << std::endl;
}

uint32_t Scenario::computeScenarioTime() const {
	double totalTime = 0;
	for (const auto& bridge : m_bridges) {
		totalTime += bridge.computeBridgeCrossingTime();
	}
	std::cout << "Total time to complete the scenario: " << totalTime << " minutes" << std::endl;
	return static_cast<uint32_t>(totalTime);
}

} //namespace scp
#include "Scenario.h"
#include "Utilities.h"

#include <yaml-cpp/yaml.h>
#include <set>

namespace scp {

Scenario::Scenario(const YAML::Node& scenario) {
	validateScenario(scenario);

	std::multiset<int> hikerSpeeds;
	for (std::size_t i = 0; i < scenario["scenario"].size(); ++i) {
		auto bridgeYaml = scenario["scenario"][i];
		validateBridge(bridgeYaml);
		for (std::size_t j = 0; j < bridgeYaml["bridge"]["hikers"].size(); ++j) {
			auto hikerYaml = bridgeYaml["bridge"]["hikers"][j];
			hikerSpeeds.insert(parseHikerSpeed(hikerYaml));
		}
		m_bridges.emplace_back(hikerSpeeds, parseBridgeLength(bridgeYaml["bridge"]["length"]));
	}
}

uint32_t Scenario::computeScenarioTime() const {
	int totalTime = 0;
	for (const auto& bridge : m_bridges) {
		totalTime += bridge.computeBridgeCrossingTime();
	}
	return totalTime;
}

} //namespace scp
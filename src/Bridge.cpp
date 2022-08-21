#include "Bridge.h"
#include "YamlParseError.h"

#include <iostream>

namespace scp {

Bridge::Bridge(const std::multiset<double>& hikerSpeeds, const double& bridgeLength)
	: m_hikerSpeeds(hikerSpeeds),
	  m_bridgeLength(bridgeLength) {
	if (m_hikerSpeeds.empty()) {
		throw YamlParseError("No hikers were provided for bridge of length: " + std::to_string(m_bridgeLength));
	}
	if (m_bridgeLength < 0) {
		throw YamlParseError("The bridge length cannot be less than 0: " + std::to_string(m_bridgeLength));
	}

	std::cout << "BRIDGE CONSTRUCTED" << std::endl;
}

double Bridge::computeBridgeCrossingTime() const {
	auto fastestHiker = *(std::prev(m_hikerSpeeds.end()));
	double totalCrossTime = 0;

	if (m_hikerSpeeds.size() >= 2) {
		// With more than 2 hikers the fastest hiker needs to re-cross the bridge with the torch
		for (auto& itr = m_hikerSpeeds.begin(); itr != std::prev(std::prev(m_hikerSpeeds.end())); ++itr) {
			double timeToCross = m_bridgeLength / *itr + m_bridgeLength / fastestHiker;
			totalCrossTime += timeToCross;
		}
		totalCrossTime += m_bridgeLength / *std::prev(std::prev(m_hikerSpeeds.end()));
	}
	else {
		totalCrossTime += m_bridgeLength / fastestHiker;
	}

	std::cout << "Total time to cross bridge: " << totalCrossTime << " minutes" << std::endl;
	return totalCrossTime;
}

} // namespace scp
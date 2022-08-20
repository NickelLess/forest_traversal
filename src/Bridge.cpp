#include "Bridge.h"
#include "YamlParseError.h"

namespace scp {

Bridge::Bridge(const std::multiset<int> hikerSpeeds, const int& bridgeLength)
	: m_hikerSpeeds(hikerSpeeds),
	  m_bridgeLength(bridgeLength) {
	if (m_hikerSpeeds.empty()) {
		throw YamlParseError("No hikers were provided for bridge of length: " + m_bridgeLength);
	}
	if (m_bridgeLength < 0) {
		throw YamlParseError("The bridge length cannot be less than 0: " + m_bridgeLength);
	}
}

uint32_t Bridge::computeBridgeCrossingTime() const {
	auto fastestHiker = *(std::prev(m_hikerSpeeds.end()));
	uint32_t totalCrossTime = 0;

	if (m_hikerSpeeds.size() >= 2) {
		// With more than 2 hikers the fastest hiker needs to re-cross the bridge with the torch
		for (auto& itr = m_hikerSpeeds.begin(); itr != std::prev(std::prev(m_hikerSpeeds.end())); ++itr) {
			uint32_t timeToCross = m_bridgeLength / *itr + m_bridgeLength / fastestHiker;
			totalCrossTime += timeToCross;
		}
		totalCrossTime += m_bridgeLength / *std::prev(std::prev(m_hikerSpeeds.end()));
	}
	else {
		totalCrossTime += m_bridgeLength / *std::prev(m_hikerSpeeds.end());
	}

	return totalCrossTime;
}

} // namespace scp
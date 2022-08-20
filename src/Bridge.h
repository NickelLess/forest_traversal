#ifndef SCALA_COMPUTE_PROJECT_BRIDGE_H
#define SCALA_COMPUTE_PROJECT_BRIDGE_H

#include <cstdint>
#include <set>

namespace scp {

class Bridge {
public:
    Bridge(const std::multiset<int> hikerSpeeds, const int& bridgeLength);
    ~Bridge() = default;

    uint32_t computeBridgeCrossingTime() const;

private:
    std::multiset<int> m_hikerSpeeds;
    int m_bridgeLength;
};

} // namespace scp

#endif // SCALA_COMPUTE_PROJECT_BRIDGE_H
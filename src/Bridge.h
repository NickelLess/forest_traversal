#ifndef SCALA_COMPUTE_PROJECT_BRIDGE_H
#define SCALA_COMPUTE_PROJECT_BRIDGE_H

#include <set>

namespace scp {

class Bridge {
public:
    Bridge(const std::multiset<double>& hikerSpeeds, const double& bridgeLength);
    ~Bridge() = default;

    double computeBridgeCrossingTime() const;

private:
    std::multiset<double> m_hikerSpeeds;
    double m_bridgeLength;
};

} // namespace scp

#endif // SCALA_COMPUTE_PROJECT_BRIDGE_H
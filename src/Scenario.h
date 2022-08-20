#ifndef SCALA_COMPUTE_PROJECT_SCENARIO_H
#define SCALA_COMPUTE_PROJECT_SCENARIO_H

#include "Bridge.h"

#include <cstdint>
#include <string>
#include <vector>

namespace YAML {
class Node;
}

namespace scp {

class Scenario {
public:
    Scenario(const YAML::Node& scenario);
    ~Scenario() = default;

    uint32_t computeScenarioTime() const;

private:
    std::vector<Bridge> m_bridges;
};

} // namespace scp

#endif // SCALA_COMPUTE_PROJECT_SCENARIO_H
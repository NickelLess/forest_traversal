#ifndef SCALA_COMPUTE_PROJECT_UTILITIES_H
#define SCALA_COMPUTE_PROJECT_UTILITIES_H

namespace YAML {
	class Node;
}

namespace scp {

void validateScenario(const YAML::Node& scenario);
void validateBridge(const YAML::Node& bridge);

int parseHikerSpeed(const YAML::Node& hiker);
int parseBridgeLength(const YAML::Node& bridge);

} // namespace scp

#endif // SCALA_COMPUTE_PROJECT_UTILITIES_H
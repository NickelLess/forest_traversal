#ifndef SCALA_COMPUTE_PROJECT_YAML_PARSE_ERROR_H
#define SCALA_COMPUTE_PROJECT_YAML_PARSE_ERROR_H

#include <exception>
#include <string>

namespace scp {

struct YamlParseError : public std::exception {
	YamlParseError(const std::string& message) : std::exception(message.c_str()) {}
};

} //namespace scp

#endif // SCALA_COMPUTE_PROJECT_YAML_PARSE_ERROR_H
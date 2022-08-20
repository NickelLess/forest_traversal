set(scp_SOURCES
	"main.cpp"
	"Bridge.cpp"
	"Utilities.cpp"
	"Scenario.cpp"
)

set(scp_HEADERS
	"Bridge.h"
	"Utilities.h"
	"Scenario.h"
	"YamlParseError.h"
	"tps/quick_arg_parser.hpp"
)

add_executable(main ${scp_SOURCES} "Bridge.h" "Utilities.h")
target_link_libraries(main yaml-cpp)

add_subdirectory(test)
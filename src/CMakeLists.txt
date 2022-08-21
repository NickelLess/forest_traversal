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

add_library(scp ${scp_SOURCES} ${scp_HEADERS})
target_link_libraries(scp yaml-cpp)
target_include_directories(scp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
install(TARGETS scp DESTINATION lib)
install(FILES ${scp_HEADERS} DESTINATION include)

add_executable(main ${scp_SOURCES})
target_link_libraries(main scp)
install(TARGETS main DESTINATION bin)

add_subdirectory(test)
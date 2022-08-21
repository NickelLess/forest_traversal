#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "Bridge.h"
#include "Scenario.h"
#include "Utilities.h"
#include "YamlParseError.h"

using namespace scp;
using namespace YAML;

// -------------------- TEST UTILITIES ------------------- //
TEST(Utilities, ValidateScenario) {
	EXPECT_THROW(validateScenario(Load("{bad_name: [1, 2, 3]}")), YamlParseError);
	EXPECT_THROW(validateScenario(Load("{scenario: {not: sequence}}")), YamlParseError);
	validateScenario(Load("{scenario: [1, 2, 3], extra_junk: junk}"));
}

TEST(Utilities, ValidateBridge) {
	EXPECT_THROW(validateBridge(Load("{bad_name: [1, 2, 3]}")), YamlParseError);
	EXPECT_THROW(validateBridge(Load("{bridge: {bad_name: 100, hikers: [1, 2, 3]}}")), YamlParseError);
	EXPECT_THROW(validateBridge(Load("{bridge: {length: 100, hikers: bad_val}}")), YamlParseError);
	validateBridge(Load("{bridge: {length: 100, hikers: [1, 2, 3]}}"));
	validateBridge(Load("{bridge: {length: 100}}"));
	validateBridge(Load("{bridge: {length: 100, extra_junk: junk}}"));
}

TEST(Utilities, ParseBridgeLength) {
	EXPECT_THROW(parseBridgeLength(Load("-2 ft")), YamlParseError);

	EXPECT_DOUBLE_EQ(100, parseBridgeLength(Load("100 ft")));
	EXPECT_DOUBLE_EQ(1.55432, parseBridgeLength(Load("1.55432 ft")));
	EXPECT_DOUBLE_EQ(0, parseBridgeLength(Load("0 ft")));
	EXPECT_DOUBLE_EQ(255, parseBridgeLength(Load("255")));
}

TEST(Utilities, ParseHikerSpeed) {
	EXPECT_THROW(parseHikerSpeed(Load("-2 ft/min")), YamlParseError);
	EXPECT_THROW(parseHikerSpeed(Load("0 ft/min")), YamlParseError);


	EXPECT_DOUBLE_EQ(100, parseHikerSpeed(Load("100 ft/min")));
	EXPECT_DOUBLE_EQ(1.55432, parseHikerSpeed(Load("1.55432 ft/min")));
	EXPECT_DOUBLE_EQ(1, parseHikerSpeed(Load("1 ft/min")));
	EXPECT_DOUBLE_EQ(255, parseHikerSpeed(Load("255")));
}

// -------------------- TEST BRIDGE ----------------------- //
TEST(Bridge, Construct) {
	EXPECT_THROW(Bridge({}, 5), YamlParseError);
	EXPECT_THROW(Bridge({ 1 }, -1), YamlParseError);
	auto bridge = Bridge({ 1, 2, 3 }, 50);
}

TEST(Bridge, ComputeBridgeCrossingTime) {
	// Single hiker case
	{
		auto bridge = Bridge({ 50 }, 100);
		EXPECT_DOUBLE_EQ(2, bridge.computeBridgeCrossingTime());
	}
	// Two hiker case
	{
		auto bridge = Bridge({ 50, 10 }, 100);
		EXPECT_DOUBLE_EQ(10, bridge.computeBridgeCrossingTime());
	}
	// Three hiker case
	{
		auto bridge = Bridge({ 50, 20, 10 }, 100);
		EXPECT_DOUBLE_EQ(17, bridge.computeBridgeCrossingTime());
	}
	// n hiker case
	{
		// Math for solution with 100ft bridge with [400, 200, 100, 50, 25, 20, 10, 5, 2, 1] ft/min hiker speeds
		// (100 / 1 + 100 / 400) +					== 100 + 1/4
		//	(100 / 2 + 100 / 400) +					== 50 + 1/4
		//  (100 / 5 + 100 / 400) +					== 20 + 1/4
		//  (100 / 10 + 100 / 400) +				== 10 + 1/4
		//  (100 / 20 + 100 / 400) +				== 5 + 1/4
		//  (100 / 25 + 100 / 400) +				== 4 + 1/4
		//  (100 / 50 + 100 / 400) +				== 2 + 1/4
		//	(100 / 100 + 100 / 400) +				== 1 + 1/4
		//	(100 / 200)								== 1/2
		auto bridge = Bridge({ 400, 200, 100, 50, 25, 20, 10, 5, 2, 1 }, 100);
		EXPECT_DOUBLE_EQ(194.5, bridge.computeBridgeCrossingTime());
	}
	// check to ensure non-clean divisions work
	{
		auto bridge = Bridge({ 22.5, 15.4, 2.3 }, 20);
		EXPECT_NEAR(10.8832, bridge.computeBridgeCrossingTime(), 0.001);
	}
	// Check to ensure hikers with same speeds work
	{
		auto bridge = Bridge({ 20, 20, 20, 10, 10 }, 100);
		EXPECT_DOUBLE_EQ(45, bridge.computeBridgeCrossingTime());
	}
}

// -------------------- TEST SCENARIO --------------------- //
TEST(Scenario, Construct) {
	EXPECT_THROW(Scenario(LoadFile("resources/test_scenario_bad_one.yaml")), YamlParseError);
	EXPECT_THROW(Scenario(LoadFile("resources/test_scenario_bad_two.yaml")), YamlParseError);
	EXPECT_THROW(Scenario(LoadFile("resources/test_scenario_empty.yaml")), YamlParseError);
	auto scenario = Scenario(LoadFile("resources/test_scenario_one.yaml"));
}

TEST(Scenario, ComputeScenarioTime) {
	{
		auto scenario = Scenario(LoadFile("resources/test_scenario_one.yaml"));
		EXPECT_DOUBLE_EQ(27, scenario.computeScenarioTime());
	}
	{
		auto scenario = Scenario(LoadFile("resources/test_scenario_two.yaml"));
		EXPECT_DOUBLE_EQ(0, scenario.computeScenarioTime());
	}
	{
		auto scenario = Scenario(LoadFile("resources/scala_compute_provided_scenario.yaml"));
		EXPECT_DOUBLE_EQ(278, scenario.computeScenarioTime());
	}
	{
		// 278 + 1801.666666667
		auto scenario = Scenario(LoadFile("resources/test_scenario_three.yaml"));
		EXPECT_DOUBLE_EQ(2079, scenario.computeScenarioTime());
	}
	{
		// 278 + 1801.666666667
		auto scenario = Scenario(LoadFile("resources/test_scenario_four.yaml"));
		EXPECT_DOUBLE_EQ(37, scenario.computeScenarioTime());
	}
}
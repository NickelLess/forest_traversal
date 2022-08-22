Forest Hiking Simulator
=======================
This repository contains a solution to a forset hiking, bridge crossing simulation problem.
In the problem, hikers encounter bridges in a forest.
Each bridge is narrow and may only hold two hikers with one torch at a time.
Hikers can only cross with a torch.
Each hiker travels at a distinct speed.
The goal of the problem is to calculate the minimal time it takes to cross the bridge.

## Problem Solution
Two hikers can cross the bridge at a time with a single torch.
When the two hikers reach the other side, the fastest hiker should return with the torch to ferry another hiker across.
This should continue until no hikers reamin on the starting side.

This means that the most efficient solution should include the fastest hiker traversing the bridge each time with every other hiker and then returning.
This will minimze the time spent returning the torch to the starting side of the bridge.
This essentially makes the solution equal to sum of the length of the bridge divided by each hiker's speed, excluding the speed of the fastest hiker, plus the length of the bridge dividied by the speed of the fastest hiker times the number of hikers minus two.
In the case of a single hiker, the time is simply the length of the bridge divided by that hiker's speed.
The solution for the specific problem provided in the question is 278 minutes.

## How to Build
This project can be built by using cmake.
This will require a c++ compiler with at least version 17 and cmake at least version 3.15.
Once those pieces are installed, the project can be built using the following commands from the root directory:
```
mkdir build
cd build
cmake ..
make -j
make install
```

The main application can then be run from the `build/bin` directory.
Tests can be run from the `build/src/test/tests.exe` or using ctest.

## Code Structure
Code is organized as follows:
```
- src/
  - test
    - resources
    TestScenarios.cpp
  -tps
    quick_argh_parser.hpp
  Bridge.h
  Bridge.cpp
  main.cpp
  Scenario.cpp
  Scenario.h
  Utilities.h
  Utilities.cpp
  YamlParseError.h
```

The most important files are listed as follows:
- `YamlParseError.h` contains c++ custom exceptions for handling errors in parsing yaml/initialization values.
- `Utilites.h` contains c++ functions to assist with the validation and parsing of yaml/strings
- `Bridge.h` contains a c++ class that solves the bridge crossing problem for a single bridge and a group of hikers.
- `Scenario.h` contains a c++ class that solves the forest scenario: IE multiple bridge crossing problems.
- `TestScenarios.cpp` contains the gtests for testing the various files listed above.

## Implementation Details
Below are implementation details associated with the problem.

### YAML format
The consumed yaml file must match the following format:
```
scenario:
  - bridge:
      length: "200 ft"
      hikers:
        - "100 ft/min"
        - "20 ft/min"
```

Root level, there should only be a `scneario` key with a sequence of bridges.
Each bridge has a key of `bridge`.
Each bridge is an object with a `length` and an optional `hikers` (Note: The first bridge MUST have a `hikers` object).
Each length is given as a string like so: "[0-9]* ft". 
Each hikers is given as a sequence of speeds, like listed above.

### Code Flow
The Code reads in a given YAML input to the Scenario class.
It validates the provided YAML, and then creates individual bridges for each sequence value in the provided scenario.
Hikers are maintained as a multiset of values which is passed as a constant reference to each Bridge as it is constructed.
Once the Scenario is constructed, the minimal time to parse a given scenario is computed using `computeScenarioTime()`

## Assumptions
Quite a few assumptions on the inputs are made:
- Bridge length is always given in `ft`
- Hiker speed is always given in `ft/min`
- Hiker speed can be a floating point value
- Bridge length could be a floating point value
- Minimal scenario time is computed as a `uint32_t`
- A bridge length must be greater than or equal to 0
- A hiker's speed my be greater than 0
- Hikers MUST exist at the first bridge
- Only a single torch is provided and only two hikers can ever cross at once.
- Hikers with the same speed may exist in a group
- Two hikers crossing the bridge must match the slower hiker's pace
- Hiker's can't leave at any point, they can only join
- Assumes that the arg provided to `--input-file` in main exists, no validation checking is performed to ensure the file is ok to work with.

## Future Ideas
Some potential ideas for expansion:
- Add multiple unit types (currently already parse units, they're just ignored)
- Add multiple scenarios for a single yaml file
- Add a varaible number of bridges and a variable number of torches at a given crossing
- Look into simplifying calculations between multiple bridges (a smarter way to calculate successive bridge times may exist without having to re-calculate every hiker's time)
- Look into using a functional interface for calculating the minimal time to cross a bridge
- Ask customer for more potential scenarios
- Add additional file validation and security parsing
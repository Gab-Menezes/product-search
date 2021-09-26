# Product Search #

## Description ##
Uses fuzzy string matching algorithm to find the best products based on search.

## Depends on ##
1. [nlohmann/json](https://github.com/nlohmann/json) to parse the json file
2. [maxbachmann/rapidfuzz-cpp](https://github.com/maxbachmann/rapidfuzz-cpp) to generate the search score

## Requirements ##
1. [Clang](https://clang.llvm.org/) or [GCC](https://gcc.gnu.org/)
    1. Clang: `sudo apt install -y clang clang++`
    2. GCC: `sudo apt install -y gcc g++`
2. [CMake](https://cmake.org/): `sudo apt install -y cmake`

## Begin ##
1. Clone this repository
2. `cd product-search`
2. Run `./init.sh` (only need to be run for the first time)

## Build ##
1. Run `./build.sh`

## Compile ##
1. Run `./compile.sh`

## Run ##
1. Run `./run.sh`

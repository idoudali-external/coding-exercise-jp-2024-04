# Ioannis Doudalis JP Morgan Coding Exercise

- [Ioannis Doudalis JP Morgan Coding Exercise](#ioannis-doudalis-jp-morgan-coding-exercise)
  - [Disclaimer](#disclaimer)
  - [Getting started](#getting-started)

## Disclaimer

- This repo is a copy of a c++ template repo that  I have to bootstrap my c++
projects. Please ignore the boiler plate code ( that is too much)
- VCs Code copilot was used as part of writing this exercise.

## Getting started

To build the project I have tried to include a docker image

The reproduction steps are:

```bash
# Build the docker image and start the container
make dev-container
# Run the bellow to initialize conan
conan profile detect --force
# Inside the container
make build-Release
# To run the tests
cd build-Release/tests
./example_test
```

The code is located under `src/libA/libA.cc`

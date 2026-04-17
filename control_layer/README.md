# han

`han` is a C++20 robotics library layered as `core`, `types`, `model`, `kin`, and `dyn` on top of Pinocchio.

## Build

On Ubuntu, configure and build with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Layout

```text
cmake/          CMake package helpers and compile options
include/han/    Public headers grouped by layer
src/            Layer build definitions and placeholder sources
examples/       Smoke example for link validation
tests/          Test entry points and per-layer placeholders
benchmarks/     Benchmark placeholder directory
docs/           Project documentation placeholder directory
```

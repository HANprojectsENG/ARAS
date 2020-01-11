# cpparas - C++ Augmented Reality Assembly Support system

## Build

The following dependencies are required to build this project:
- CMake
- GTKmm 3

Build the project with the following commands:
```
mkdir build && cd build
cmake ..
make -j
```

The resulting program can be executed with
```
./cpparas
```

## Debugging

To build the project with debug symbols enabled, the cmake variable
`CMAKE_BUILD_TYPE` needs to be set to `Debug`.
Replace the `cmake` invocation with:
```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## Documentation

The following dependencies are required to build the Doxygen documentation for
this project:
- Doxygen
- GraphViz

To generate the documentation, the CMake BUILD_DOC flag needs to be enabled.
Replace the `cmake` invocation with:
```
cmake -DBUILD_DOC=1 ..
```

Once the documentation is compiled, it can be accessed by opening
`./docs/html/index.html` in the browser.

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

## Documentation

The following dependencies are required to build the Doxygen documentation for
this project:
- Doxygen
- GraphViz

To generate the documentation, run the build with the CMake BUILD_DOC
flag enabled:
```
mkdir build && cd build
cmake -DBUILD_DOC=ON ..
make -j
```

Once the documentation is compiled, it can be accessed by opening
`./docs/html/index.html` in your browser.

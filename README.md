# Math Library
Math library programmed in C++ built for graphics & game engine programming.

## Library Supports
- Arithmetic
- Degree
- Radian
- Vector 2D
- Vector 3D
- Vector 4D
- Matrix 2x2
- Matrix 3x3
- Matrix 4x4
- Quaternion

## Other Features
- The math library uses template types to support all arithmetic types.
- Library is compiled as a static lib (`.lib`) via cmake

## Install & Build
1. Clone the repository
2. Add a `build/` folder in the root of the project
3. Open the terminal in the `build/` folder and run the cmake command `cmake ..`
4. In the `build/` folder a `.sln` file should appear, open it & build the solution. This should create a `.lib` file for the math library
5. Copy the `.lib` and the folder `LibMath/` in `source/include/` into your project

## Planned Features
- 2D & 3D Geometry types (box, circle) & intersection checks
- Additional unit tests for more in-depth testing off all supported math types.

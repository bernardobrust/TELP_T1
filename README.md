# First assigment for Special Topics in Programming Languages
Cauã and Bernardo's repo

## Idea
This assigment aims to solve the situation proposed at `analysis/TELP Key Ideas.pdf`. That is, 
optimize the detection of the nearest ball in a dynamic pool table.

We aim to do this by mixing BVH (bounding volume hierarchies) and ODEs (ordinary differential equations).

## Building

### Using GCC on macOS (recommended for `std::execution::par_unseq`)

Apple Clang uses libc++, which does not implement the C++17 parallel execution policies. To get `std::execution::par_unseq` (and parallel algorithms in general) working, use GCC from Homebrew:

```bash
brew install gcc
mkdir -p build && cd build
CXX=$(brew --prefix gcc)/bin/g++-14 cmake ..   # or g++-13, depending on installed version
make -j$(sysctl -n hw.logicalcpu)
./TELP_T1
```

Replace `g++-14` with your installed version (e.g. `g++-13`). Check with `ls $(brew --prefix gcc)/bin/g++*`.

### Using the default compiler (Clang on macOS)

With Apple Clang the project will not compile as-is because of `std::execution::par_unseq`. Use GCC as above, or add a libc++ fallback in `src/add_vecs.h` (sequential transform when `_LIBCPP_VERSION` is defined).

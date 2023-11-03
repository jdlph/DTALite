# Cross-Platform DTALite

This repository has two branches: **main** and **feature/multimodal**. While branch feature/multimodal is set to track the upstream [asu-trans-ai-lab/DTALite](https://github.com/asu-trans-ai-lab/DTALite), the main branch is an **independent development** from [asu-trans-ai-lab/DTALite](https://github.com/asu-trans-ai-lab/DTALite) after [pull request #8](https://github.com/asu-trans-ai-lab/DTALite/pull/8). 

Branch main aims to provide a clean and common C++ code base (over its original implementation) to build both executable and shared library of DTALite across platforms. In this branch, we only resolve its most critical issues as a minimal effort towards reliability and portability, which include

1. platform-specific implementation,
2. memory leak,
3. code bloating (i.e., excessively large executable),
4. mix use of the C and C++ standard libraries.

As **it still has legacy code which either does not represent the best practices or could be optimized for better performance**, a deep refactoring is still needed and on the way as a separate project. The details are summarized in **[Refactoring](#refactoring)**.

The development of DTALite in Python has been halted and fully merged with [Path4GMNS](https://github.com/jdlph/Path4GMNS) (which originates from the same sorce code). The original source code and binary files are all deprecated and moved to the [archive folder](https://github.com/jdlph/DTALite/tree/main/archive) for reference only.

> [!WARNING]
> This repository has been **DEPRECATED**, and will be **REMOVED** some time. Please check [TransOMS](https://github.com/jdlph/TransOMS) for the latest development.

## Build DTALite
We use the cross-platform tool CMake to define the building process.

*Build the executable using CMake and run it with NeXTA*
```
# from the root directory of src (i.e., DTALite/src_cpp/src)
$ mkdir build
$ cd build
$ cmake .. -DBUILD_EXE=ON
$ cmake --build .
```

*Build the shared library using CMake and use it with a [Python interface](https://github.com/jdlph/Path4GMNS)*
```
# from the root directory of src (i.e., DTALite/src_cpp/src)
$ mkdir build
$ cd build
$ cmake .. -DBUILD_EXE=OFF
$ cmake --build .
```

You can remove -DBUILD_EXE=ON or -DBUILD_EXE=OFF if you prefer to manually change the value of BUILD_EXE in [CMakeLists.txt](https://github.com/jdlph/DTALite/blob/main/src_cpp/src/CMakeLists.txt).

*Windows Users*

A classic Visual Studio solution file is shipped as well along with the project file to **build executable only on Windows** for the convenience of users who are not familiar with CMake. **Note that** they are not built on CMakeLists.txt. If you are planning to build the shared library of DTALite, there are three ways.

1. Let CMake automatically generate solution and project files for you by using the commands above. It is the easiest and recommmended way;
2. [Create your own Visual Studio project](https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-projects-solutions?view=vs-2019) under the shipped solution;
3. [Create new CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160) by including the embedded [CMakeLists.txt](https://github.com/jdlph/DTALite/blob/main/src_cpp/src/CMakeLists.txt).

## Refactoring

We have launched another project in a private repo [DTALite_Refactoring](https://github.com/jdlph/DTALite_Refactoring) to further refactor it using modern C++ (mainly C++11 and C++14) and some well-established C++ best practices (e.g., the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)) with the potential improvements over its original implementation in the following areas. It will be made public once it is mature.

1. Readability and maintainability. Major tasks will include removing duplicate source file inclusions and unused variables, fixing some bad namings and formats, replacing functions from the C standard library with the C++ equivalents, adopting a multi-file structure to group components by their functionalities, separating implementations of class member functions from their declarations unless they are suitable for inline, using list_initializer in the default constructor to initialize members, substituting NULL and typedef with nullptr and using respectively, and so on;
2. Performance. This can be achieved through move semantics (C++11) to avoid unnecessary copying, the new hash-based unordered_map (C++11) over the tree-based map (C++98) to improve retrieval speed, and constexpr (C++11) to shift some run-time evaluations to compilation. Furthermore, a slightly faster deque implementation of the modified label correcting (MLC) algorithm for calculating shortest paths will be implemented to replace the existing one;
3. Security. It is mainly about using smart pointers (C++11 and C++14) to provide better memory management (e.g., fix some known memory leaks);
4. Portability. This will be the natural result from the prior three enhancements by replacing the Visual Studio solution file with a cross-platform CMakeLists.txt. Besides, better casting (via explicit conversion), size_t, and size_type will be appropriately used to further improve these four areas.
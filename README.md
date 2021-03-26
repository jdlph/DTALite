# Cross-Platform DTALite

This repo is an **independent development** from [asu-trans-ai-lab/DTALite](https://github.com/asu-trans-ai-lab/DTALite) after [pull request #8](https://github.com/asu-trans-ai-lab/DTALite/pull/8). It aims to provide a clean and common C++ code base (over its original implementation) to build both executable and shared library of DTALite across platforms. As it still has legacy code which either does not represent the best practices or could be optimized for better performance, we have lanuched a project to further refactor it using modern C++ (mainly C++11 and C++14) in a private repo [DTALite_Refactoring](https://github.com/jdlph/DTALite_Refactoring). It will be made public once it is mature.

The development of DTALite in Python has been halted and partially merged with [Path4GMNS](https://github.com/jdlph/Path4GMNS), which originates from the same sorce code. It will be resumed in the future when Path4GMNS is fully implemented.

The legacy source and binary files are all deprecated and moved to the [archive folder](https://github.com/jdlph/DTALite/tree/main/archive) for referrence only.

## Build DTALite
We use the cross-platform tool CMake to define the building process. A classic Visual Studio solution file is shipped as well along with the project file to **build executable only on Windows** for the convenience of users who are not familar with CMake. **Note that** they are not built on CMakeLists.txt. You will still need to [create your own Visual Studio project](https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-projects-solutions?view=vs-2019) to build the shared library of DTALite under this solution or [create new CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160) by including the embedded [CMakeLists.txt](https://github.com/jdlph/DTALite/blob/main/src_cpp/src/CMakeLists.txt).


Build the executable using CMake and run it with NEXTA.
```
# from the root directory of src (i.e., DTALite/src_cpp/src)
$ mkdir build
$ cd build
$ cmake .. -DBUILD_EXE=ON
$ cmake --build .
```

Build the shared library using CMake and use it with a [Python interface](https://github.com/jdlph/Path4GMNS).
```
# from the root directory of src (i.e., DTALite/src_cpp/src)
$ mkdir build
$ cd build
$ cmake .. -DBUILD_EXE=OFF
$ cmake --build .
```

You can remove -DBUILD_EXE=ON or -DBUILD_EXE=OFF if you prefer to manually change the value of BUILD_EXE in [CMakeLists.txt](https://github.com/jdlph/DTALite/blob/main/src_cpp/src/CMakeLists.txt).

## Get Started with DTALite
### Step 1: White Paper and Application
*Zhou, Xuesong, and Jeffrey Taylor. "[DTALite: A queue-based mesoscopic traffic simulator for fast model evaluation and calibration.](https://www.tandfonline.com/doi/full/10.1080/23311916.2014.961345)" Cogent Engineering 1.1 (2014): 961345.*

*Marshall, Norman L. "[Forecasting the impossible: The status quo of estimating traffic flows with static traffic assignment and the future of dynamic traffic assignment.](https://www.sciencedirect.com/science/article/pii/S2210539517301232)" Research in Transportation Business & Management 29 (2018): 85-92.*

### Step 2: Youtube Teaching Videos on Use of DTALite/NEXTA Packages
[NeXTA/DTALite Workshop Webinar](https://www.youtube.com/channel/UCUHlqojCQ4f7VvqroUhbaFA) by Jeff Taylor

### Step 3: Mini-Lesson on the Internal Algorithmic Details
[Mini-lessson](https://youtu.be/rorZAhNNOf0): What is the best way to learn dynamic traffic simulation and network assignment for a beginner? Do you want to integrate a powerful traffic simulator in your deep learning framework? We would like to offer a collaborative learning experience through 500 lines of python codes and real-life data sets. This is part of our mini-lessons through teaching dialog.

[Python source code](https://github.com/jdlph/DTALite/tree/main/src_py)

[C++ source code](https://github.com/jdlph/DTALite/tree/main/src_cpp/src)

[Testing environment on the shared library of DTALite](https://github.com/jdlph/Path4GMNS/tree/master/tests)

### Other References: 
**1. Parallel computing algorithms**

*Qu, Y., & Zhou, X. (2017). Large-scale dynamic transportation network simulation: A space-time-event parallel computing approach. Transportation research part c: Emerging technologies, 75, 1-16.*

**2. OD demand estimation**

*Lu, C. C., Zhou, X., & Zhang, K. (2013). Dynamic origin–destination demand flow estimation under congested traffic conditions. Transportation Research Part C: Emerging Technologies, 34, 16-37.*

**3. Simplified emission estimation model**

*Zhou, X., Tanvir, S., Lei, H., Taylor, J., Liu, B., Rouphail, N. M., & Frey, H. C. (2015). Integrating a simplified emission estimation model and mesoscopic dynamic traffic simulator to efficiently evaluate emission impacts of traffic management strategies. Transportation Research Part D: Transport and Environment, 37, 123-136.*

**4. Eco-system optimal time-dependent flow assignment**

*Lu, C. C., Liu, J., Qu, Y., Peeta, S., Rouphail, N. M., & Zhou, X. (2016). Eco-system optimal time-dependent flow assignment in a congested network. Transportation Research Part B: Methodological, 94, 217-239.*

**5. Transportation-induced population exposure assessment**

*Vallamsundar, S., Lin, J., Konduri, K., Zhou, X., & Pendyala, R. M. (2016). A comprehensive modeling framework for transportation-induced population exposure assessment. Transportation Research Part D: Transport and Environment, 46, 94-113.*

**6. Integrated ABM and DTA**

*Xiong, C., Shahabi, M., Zhao, J., Yin, Y., Zhou, X., & Zhang, L. (2020). An integrated and personalized traveler information and incentive scheme for energy efficient mobility systems. Transportation Research Part C: Emerging Technologies, 113, 57-73.*

**7. State-wide transportation modeling**

*Zhang. L. (2017) Maryland SHRP2 C10 Implementation Assistance – MITAMS: Maryland Integrated Analysis Modeling System, Maryland State Highway Administration*

**8. Workzone applications**

*Schroeder, B, et al. Work zone traffic analysis & impact assessment. (2014) FHWA/NC/2012-36. North Carolina. Dept. of Transportation. Research and Analysis Group.*
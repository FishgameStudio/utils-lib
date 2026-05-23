<div align="center">

# UtilitiesLibrary
> A simple & all-purpose utilities colletion!

[**Explore the docs >>>**](docs)

![Stars](https://img.shields.io/github/stars/FishgameStudio/utils-lib?style=social)
![Forks](https://img.shields.io/github/forks/FishgameStudio/utils-lib?style=social)
![Watchers](https://img.shields.io/github/watchers/FishgameStudio/utils-lib?style=social)
![Issues](https://img.shields.io/github/issues/FishgameStudio/utils-lib)
![PRs](https://img.shields.io/github/issues-pr/FishgameStudio/utils-lib)

![Version](https://img.shields.io/badge/version-1.0-orange)
[![C++](https://img.shields.io/badge/C++-26-blue)](https://isocpp.org)
[![Python](https://img.shields.io/badge/python-3.14-blue)](https://python.org)
![License](https://img.shields.io/github/license/FishgameStudio/utils-lib)

</div>

<details>
    <summary>Table of Contents</summary>
    <li>
        <a href="#introduction">Introduction</a>
    </li>
    <li>
        <a href="#core-features">Core Features</a>
    </li>
    <li>
        <a href="#suitable-scenarios">Suitable Scenarios</a>
    </li>
    <li>
        <a href="#getting-started">Getting Started</a>
        <ul>
          <a href="#how-to-use">How To Use</a>
        </ul>
        <ul>
          <a href="#how-to-build">How To Build</a>
          <ul>
              <a href="#environment-required">Environment Required</a>
          </ul>
          <ul>
              <a href="#compiling-code">Compiling Code</a>
          </ul>
        </ul>
    </li>
    <li>
        <a href="#roadmap">Roadmap</a>
    </li>
    <li>
        <a href="#contributing">Contributing</a>
    </li>
    <li>
        <a href="#license">License</a>
    </li>
    <li>
        <a href="#contact">Contact</a>
    </li>
    <li>
        <a href="#acknowledgments">Acknowledgments</a>
    </li>
    <li>
        <a href="#conclusion">Conclusion</a>
    </li>
</details>


## Introduction
🚀A concise, practical, cross-platform general-purpose utility library written in standard modern C++, integrated with **file operation toolkit, mathematical common function toolkit and full-featured date-time processing toolkit**, tailored for daily development, framework construction, embedded auxiliary development and lightweight project rapid iteration scenarios.

A large number of scattered code snippets and fragmented utility functions exist in various development repositories; most of them are either fragmented and difficult to manage, lack unified specification encapsulation, have messy interface styles, fail to take cross-platform compatibility into account, or are overly bloated with redundant functions that increase project volume. **Few lightweight aggregated utility libraries can stably cover file traversal judgment, common mathematical calculations and comprehensive time processing**. None of the existing open-source tool libraries fully meet my actual needs for **clean structure, zero redundant dependencies, consistent calling logic, cross-platform universality and easy secondary expansion**, so I developed UtilitiesLibrary independently to build a unified, neat and long-term maintainable personal general basic tool library.

Here’s why UtilitiesLibrary is well-suited for integration into daily development projects:

- You can focus more energy on core business logic writing and project architecture design, instead of write repetitive file checking, time conversion and mathematical auxiliary calculation code in every new project.
- It adopts unified standardized interface design, consistent naming specifications and neat code layering, eliminating the trouble of adapting different styles of scattered tool functions.
- Fully supports cross-platform compatibility, perfectly compatible with Windows, Linux, macOS mainstream operating systems and works steadily on desktop, server and embedded platforms.
- Strictly follow C++ syntax specifications, abandon weird obscure writing, retain high code readability while ensuring operational efficiency, making later extension and debugging effortless.
- Three core modules are independently decoupled, users can reference and use them separately as needed, and will not introduce extra redundant code to increase project compilation volume and running overhead.
- Rich and complete built-in practical functions: **cross-platform file time acquisition, filename parsing & hidden file judgment, common mathematical calculation encapsulation, timestamp mutual conversion, date comparison judgment, year/month/day/hour/minute/second independent extraction and other practical functions**, covering most basic development demands.

Of course, this basic general tool library cannot cover all professional scenario-specific low-level functions such as network communication, hardware underlying calling and high-concurrency scheduling. I will continue to maintain and iterate UtilitiesLibrary later, continuously enrich practical general functions, optimize internal logic details, fix potential compatibility bugs, and expand more lightweight auxiliary tool modules according to actual development demands. All developers are welcome to star this project, share valuable optimization ideas and function expansion demands through Issues, and jointly polish this practical lightweight basic utility library. Every user's recognition and use is the biggest power to promote the continuous improvement of this project.

## Core Features
- ✨ **Standard Modern C++ Implementation**
  Written based on mainstream modern C++ standards with clean structure and easy integration. When building Python bindings, `pybind11` is required.
- 📂 **Full-Featured Cross-Platform File Toolkit**
  Support file & folder traversal, pure filename extraction (remove suffix), hidden file judgment, cross-platform stable acquisition of file modification time, fast judgment of files modified on the current day and other common file operation functions.
- 🧮 **Practical Common Mathematical Function Encapsulation**
  Integrate daily development commonly used numerical calculation, data conversion, range constraints and other basic mathematical auxiliary interfaces, simplify tedious numerical processing logic.
- ⏰ **Complete Date-Time Processing System**
  Realize second/millisecond-level timestamp acquisition, timestamp and standard date-time string mutual conversion, independent extraction of individual fields including year/month/day/hour/minute/second, and fast comparison judgment of time points.
- 🔄 **Unified Cross-Platform Compatibility Logic**
  Abandon platform-specific exclusive APIs, adopt standard library general implementation scheme, and all core functions run stably and consistently on Windows / Linux / macOS.
- 🧩 **Module Decoupling & Independent Reference**
  File, mathematics, date and time three major core modules are completely decoupled, support separate introduction and separate use, flexible matching different project development demands.
- 🧹 **Neat Code Structure & Easy Expansion**
  Internal code layering is clear, function classification is clear, reserved function expansion interface, convenient for users to add personalized custom utility functions on the basis of the original framework.
- 🎯 **Lightweight & Low Overhead**
  Focus on practical basic functions, abandon redundant fancy functions, occupy low resources, and can be used not only for desktop projects, but also for lightweight embedded auxiliary development scenarios.

## Suitable Scenarios
- Daily personal C++ practice projects and small functional tool development
- Rapid development of lightweight desktop client and console programs
- Basic file management and time statistics function development of server side auxiliary components
- Embedded upper computer auxiliary development and simple MCU auxiliary logic writing
- Framework basic underlying tool function aggregation and project public basic code unification management
- Scenarios that need to unify basic utility functions and reduce repeated wheel-making behavior
- Student programming learning, code standardization training and usual development code accumulation sorting

## Getting Started
Here is an example to build.

At first, please clone the repository on your local computer:
```bash
git clone https://github.com/FishgameStudio/utils-lib.git
```

### How to Use

[**Explore the docs >>>**](docs)

*Please keep the copyright comments in the header file while using.*
*if you modified our source code, please insert these lines into your code:*
```cpp
// Modified by [Your Name] [Modified Date]
// Changes: [Modified Content]
```

### How To Build
This is an example to compile & run the code.

#### Environment Required
To compile the code, you need:
- Python official launcher(version 3+)
- pip (26+)
- clang/clang++ latest version(22).
- gcc/g++ latest version(16.1).
- MSVC latest version(14.50.35710).

*Your compiler must support libc++.*

#### Compiling Code
This is an example of the compiling code.
```bash
# Install pybind11
pip install pybind11
# clang++
clang++ test/your_code.cpp -Wall -std=c++26 -stdlib=libc++ -fexperimental-library -I./utils/ -o build/your_program
# g++
g++ -o build/your_program -Wall -std=c++26 -I./utils/ test/your_code.cpp
# MSVC (no escape character)
cl /O2 /W4 /std:c++26 /I.\utils\ /Fobuild\ /Febuild\your_program.exe test\your_code.cpp

# Run
build/your_program
```

## NOTICE
This project now includes optional Python binding support via `pybind11`. If you use the Python integration, make sure `pybind11` is installed and available during build.

## Roadmap
- [x] String library
- [x] Requests library
- [x] DateTime library
- [x] Hashlib

See the [open issues](https://github.com/FishgameStudio/utils-lib/issues) for a full list of proposed features (and known issues).

## Contributing

Contributions are what make the open source community such an amazing place **to learn, inspire, and create**. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please **fork the repo** and **create a pull request**. You can also simply open an issue with the tag **"enhancement"**.
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Top contributors:

<a href="https://github.com/FishgameStudio/utils-lib/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=FishgameStudio/utils-lib" alt="contrib.rocks image" />
</a>

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.


## Contact

Nicola Grey - [popxhxh@outlook.com](mailto:popxhxh@outlook.com)

Project Link: [https://github.com/FishgameStudio/utils-lib](https://github.com/FishgameStudio/utils-lib)


## Acknowledgments

* [othneildrew/Best-README-Template](https://github.com/othneildrew/Best-README-Template)
* [pybind/pybind11](https://github.com/pybind/pybind11)


## Conclusion
Hope this lightweight UtilitiesLibrary can assist you in daily C++ development, simplify repetitive basic logic writing, and speed up your project construction efficiency.

Every star, fork and sincere feedback means a lot to me. You are warmly welcome to submit issues for bugs feedback and function suggestions, or send pull requests to participate in code optimization and function iteration, so as to polish and improve this utility library together.

If you find this project practical and helpful, don’t forget to hit **Star** and **Fork**. All valuable opinions and ideas are **sincerely welcomed**. Thank you very much for your support!
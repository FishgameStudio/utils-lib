# This CMakeLists.txt file is for building Python APIs instead of your C++ usage.
# You don't need this if you only want to use the C++ APIs.

cmake_minimum_required(VERSION 3.15)

project(utils-lib)

# Find for python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Import pybind11
include_directories(${Python3_INCLUDE_DIRS})
execute_process(
  COMMAND python3 -m pybind11 --includes
  OUTPUT_VARIABLE PYBIND11_INCLUDES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)


add_library(
    FileLib MODULE
    utils/file/pybind_file.cpp
)
add_library(
    DatetimeLib MODULE
    utils/datetime/pybind_datetime.cpp
)
add_library(
    StringLib MODULE
    utils/string/pybind_string.cpp
)
add_library(
    TimerLib MODULE
    utils/timer/pybind_timer.cpp
)
add_library(
    ThreadPoolLib MODULE
    utils/threadpool/pybind_threadpool.cpp
)

foreach(lib FileLib DatetimeLib StringLib TimerLib ThreadPoolLib)
    # Enable C++23 standard
    target_compile_features(${lib} PRIVATE cxx_std_23)
    target_include_directories(${lib} PRIVATE ${Python3_INCLUDE_DIRS})

    # Let the compiler know that this is a Python extension module
    set_target_properties(${lib} PROPERTIES
        COMPILE_FLAGS "${PYBIND11_INCLUDES}"
        PREFIX ""
        # Output to the py_utilslib directory.
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/py_utilslib
    )

    # Link against the Python libraries
    target_link_libraries(${lib} PRIVATE Python3::Python)

    # macOS platform suffix
    if(APPLE)
        set_target_properties(${lib} PROPERTIES SUFFIX ".so")
    endif()

    # Windows platform suffix
    if(WIN32)
        set_target_properties(${lib} PROPERTIES SUFFIX ".pyd")
    endif()
endforeach()
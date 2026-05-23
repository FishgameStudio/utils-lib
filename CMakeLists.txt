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

foreach(lib FileLib DatetimeLib StringLib)
    # Enable C++23 standard
    target_compile_features(${lib} PRIVATE cxx_std_23)

    # Let the compiler know that this is a Python extension module
    set_target_properties(${lib} PROPERTIES
        COMPILE_FLAGS "${PYBIND11_INCLUDES}"
        PREFIX ""
    )

    # macOS platform suffix
    if(APPLE)
        set_target_properties(${lib} PROPERTIES SUFFIX ".so")
    endif()

    # Windows platform suffix
    if(WIN32)
        set_target_properties(${lib} PROPERTIES SUFFIX ".pyd")
    endif()
endforeach()
cmake_minimum_required(VERSION 3.18)
project(utils-lib LANGUAGES CXX)

# find python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# fnid pybind11
find_package(pybind11 CONFIG REQUIRED)

# define module
pybind11_add_module(FileLib      utils/file/pybind_file.cpp)
pybind11_add_module(DatetimeLib  utils/datetime/pybind_datetime.cpp)
pybind11_add_module(StringLib    utils/string/pybind_string.cpp)
pybind11_add_module(TimerLib      utils/timer/pybind_timer.cpp)
pybind11_add_module(ThreadPoolLib utils/threadpool/pybind_threadpool.cpp)

# set properties
set(TARGETS
    FileLib DatetimeLib StringLib TimerLib ThreadPoolLib
)
foreach(t ${TARGETS})
    target_compile_features(${t} PRIVATE cxx_std_23)

    # output dir
    set_target_properties(${t} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/py_utilslib
    )

    # suffixes
    if(WIN32)
        set_target_properties(${t} PROPERTIES SUFFIX ".pyd")
    else()
        set_target_properties(${t} PROPERTIES SUFFIX ".so")
    endif()
endforeach()
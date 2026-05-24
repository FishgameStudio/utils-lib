#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "timer.h"

namespace py = pybind11;

PYBIND11_MODULE(TimerLib, m) {
    m.doc() = "Timer & Stopwatch C++ binding for Python";

    py::class_<timer::Stopwatch>(m, "Stopwatch")
        .def(py::init<>())
        .def("start", &timer::Stopwatch::start, "Start the stopwatch")
        .def("stop", &timer::Stopwatch::stop, "Stop the stopwatch")
        .def("reset", &timer::Stopwatch::reset, "Reset time to 0")
        .def("get_time", &timer::Stopwatch::get_time, "Get current time (ms)")
        .def("terminate", &timer::Stopwatch::terminate, "Terminate the timer thread")
        .def("is_running", &timer::Stopwatch::is_running, "Check if running")
        .def("__repr__", [](const timer::Stopwatch& self) {
            return "<Stopwatch object>";
        });

    py::class_<timer::Timer>(m, "Timer")
        .def(py::init<unsigned long long, std::function<void()>>(),
             py::arg("interval_ms"), py::arg("func"),
             "Create a timer: interval(ms), callback function")
        .def("stop", &timer::Timer::stop, "Stop the timer")
        .def("continue_", &timer::Timer::continue_, "Continue the timer")
        .def("__repr__", [](const timer::Timer&) {
            return "<Timer object>";
        });
}
// pybind11 bindings for datetime utilities
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include "time.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_datetime, m) {
    m.doc() = "A datetime module implemented in C++ using pybind11";

    m.def("timestamp", &datetime::timestamp, "Seconds since epoch as integer");
    m.def("timestamp_ms", &datetime::timestamp_ms, "Milliseconds since epoch as integer");
    m.def("current_date_time_string", &datetime::currentDateTimeString, "Formatted current date-time string");
    m.def("current_year", &datetime::currentYear);
    m.def("current_month", &datetime::currentMonth);
    m.def("current_day", &datetime::currentDay);
    m.def("current_hour", &datetime::currentHour);
    m.def("current_minute", &datetime::currentMinute);
    m.def("current_second", &datetime::currentSecond);
    m.def("sleep", &datetime::sleep, "Sleep for given seconds");
    m.def("sleep_ms", &datetime::sleepms, "Sleep for given milliseconds");

    py::class_<datetime::DATETIME>(m, "Datetime")
        .def(py::init<>())
        .def_readwrite("year", &datetime::DATETIME::year)
        .def_readwrite("month", &datetime::DATETIME::month)
        .def_readwrite("day", &datetime::DATETIME::day)
        .def_property("minute",
            [](const datetime::DATETIME &d) { return d.min; },
            [](datetime::DATETIME &d, int v) { d.min = v; })
        .def_property("second",
            [](const datetime::DATETIME &d) { return d.sec; },
            [](datetime::DATETIME &d, int v) { d.sec = v; })
        .def_property("timestamp",
            [](const datetime::DATETIME &d) { return d.ts; },
            [](datetime::DATETIME &d, long long v) { d.ts = v; })
        .def("__repr__", [](const datetime::DATETIME &d) {
            return std::string("<Datetime year=") + std::to_string(d.year)
                + " month=" + std::to_string(d.month)
                + " day=" + std::to_string(d.day)
                + " minute=" + std::to_string(d.min)
                + " second=" + std::to_string(d.sec)
                + " ts=" + std::to_string(d.ts) + ">";
        })
        .def("__lt__", [](const datetime::DATETIME &a, const datetime::DATETIME &b) { return a < b; })
        .def("__gt__", [](const datetime::DATETIME &a, const datetime::DATETIME &b) { return a > b; })
        .def("__eq__", [](const datetime::DATETIME &a, const datetime::DATETIME &b) { return a == b; })
        .def("__ne__", [](const datetime::DATETIME &a, const datetime::DATETIME &b) { return a != b; });
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include "string.h"

namespace py = pybind11;

PYBIND11_MODULE(StringLib, m) {
    m.doc() = "A string utilities module implemented in C++ using pybind11.";

    auto pyOutOfRange = py::register_exception<str::OutOfStringRange>(m, "OutOfStringRange", PyExc_IndexError);
    py::register_exception<str::IndexUnderflow>(m, "IndexUnderflow", pyOutOfRange.ptr());

    m.def("len", &str::len, "Return the length of a string.", py::arg("s"));
    m.def("left", &str::left, "Return the leftmost `len` characters.", py::arg("s"), py::arg("len"));
    m.def("right", &str::right, "Return the rightmost `len` characters.", py::arg("s"), py::arg("len"));
    m.def("mid", &str::mid, "Return a substring from `start` with optional `len`.", py::arg("s"), py::arg("start"), py::arg("len") = std::string::npos);
    m.def("getleft", &str::getleft, "Return leftmost `len` characters or original string on error.", py::arg("s"), py::arg("len"));
    m.def("getright", &str::getright, "Return rightmost `len` characters or original string on error.", py::arg("s"), py::arg("len"));
    m.def("getmid", &str::getmid, "Return a substring or original string on error.", py::arg("s"), py::arg("start"), py::arg("len") = std::string::npos);

    m.def("upper", &str::upper, "Convert the string to uppercase.", py::arg("s"));
    m.def("lower", &str::lower, "Convert the string to lowercase.", py::arg("s"));
    m.def("title", &str::title, "Convert the string to title case.", py::arg("s"));
    m.def("capitalize", &str::capitalize, "Capitalize the first character.", py::arg("s"));
    m.def("caseswap", &str::caseswap, "Swap case for each character.", py::arg("s"));
    m.def("strip", &str::strip, "Trim leading and trailing spaces.", py::arg("s"));
    m.def("split", &str::split, "Split a string by separator.", py::arg("s"), py::arg("sep"));
    m.def("count", &str::count, "Count occurrences of a character.", py::arg("s"), py::arg("subs"));
    m.def("find", &str::find, "Find a substring and return its position.", py::arg("s"), py::arg("subs"));
    m.def("repeat", &str::repeat, "Repeat a string `time` times.", py::arg("s"), py::arg("time") = 1);
    m.def("reverse", &str::reverse, "Reverse a string.", py::arg("s"));
    m.def("replace", &str::replace, "Replace all occurrences of `oldsubs` with `newsubs`.", py::arg("s"), py::arg("oldsubs"), py::arg("newsubs"));
    m.def("input", &str::input, "Get input from the user with an optional prompt.", py::arg("prompt") = "");
    m.def("inputpasswd", &str::inputpasswd, "Get password input from the user with an optional prompt.", py::arg("prompt") = "Password: ");
}


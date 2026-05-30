/* Pybind11 binding for thread pool. */

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "threadpool.h"

namespace py = pybind11;
using namespace threadpool;

PYBIND11_MODULE(ThreadPoolLib, m) {
    m.doc() = "Thread pool for concurrent task execution";

    py::class_<THREADPOOL>(m, "THREADPOOL")
        .def(py::init<size_t>(), "Create thread pool with given thread count")
        
        .def("execute", &THREADPOOL::execute<py::function>, "Submit a function to thread pool")
        
        .def("available_threads", &THREADPOOL::available_threads, "Get number of idle threads")
        
        .def("wait_all", &THREADPOOL::wait_all, "Wait for all tasks to finish");
}
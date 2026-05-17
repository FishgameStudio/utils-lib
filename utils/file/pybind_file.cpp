// pybind11 bindings for file utilities
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include "file.h"

namespace py = pybind11;

PYBIND11_MODULE(_file, m) {
    m.doc() = "File utilities module powered by pybind11.";

    py::register_exception<file::FileException>(m, "FileException", PyExc_RuntimeError);
    py::register_exception<file::FileNotFoundException>(m, "FileNotFoundException", m.attr("FileException"));
    py::register_exception<file::FileReadFailException>(m, "FileReadFailException", m.attr("FileException"));
    py::register_exception<file::FileWriteFailException>(m, "FileWriteFailException", m.attr("FileException"));
    py::register_exception<file::FileOpenFailException>(m, "FileOpenFailException", m.attr("FileException"));
    py::register_exception<file::FileInvalidAttributesException>(m, "FileInvalidAttributesException", m.attr("FileException"));

    m.def("exists", &file::exists, "Check if a file or directory exists.");
    m.def("is_regular_file", &file::isRegular, "Check whether a path is a regular file.");
    m.def("relative_path_of", &file::relativePathOf, "Get relative path of a file.");
    m.def("abs_path_of", &file::absPathOf, "Get absolute path of a file.");
    m.def("extension_of", &file::extensionOf, "Get the extension of a file.");
    m.def("stem_of", &file::stemOf, "Get the filename stem.");
    m.def("is_read_only", &file::isReadOnly, "Check whether a file is read-only.");
    m.def("file_size", &file::size, "Get the size of a file in bytes.");
    m.def("is_hidden", &file::isHidden, "Check whether a file is hidden.");

    m.def("get_working_dir", &file::getWorkingDir, "Get the current working directory.");
    m.def("change_dir", &file::chdir, "Change the current working directory.");
    m.def("copy_file", &file::copy, "Copy a file.");
    m.def("move_file", &file::move, "Move a file.");
    m.def("rename_file", &file::rename, "Rename a file.");
    m.def("is_valid_filename", &file::isValidFilename, "Check whether a filename is valid.");
    m.def("make_dir", &file::makeDir, "Create directories recursively.");
    m.def("remove_file", &file::removeFile, "Remove a file.");
    m.def("remove_dir", &file::removeDir, "Remove a directory and its contents.");

    m.def("read_file", &file::readFile, "Read text from a file.");
    m.def("read_binary", &file::readBinary, "Read binary data from a file.");
    m.def("write_file", &file::writeFile, "Write text to a file.");
    m.def("append_file", &file::appendFile, "Append text to a file.");
    m.def("write_binary", &file::writeBinary, "Write binary data to a file.");

    py::class_<file::TempFile>(m, "TempFile")
        .def(py::init<const std::string&>(), py::arg("file") = "")
        .def("get_content", &file::TempFile::getContent)
        .def("get_binary", &file::TempFile::getBinary)
        .def("get_name", &file::TempFile::getName)
        .def("remove", &file::TempFile::remove);
}

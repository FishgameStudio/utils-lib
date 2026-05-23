from setuptools import setup
from setuptools.command.build_ext import build_ext
import subprocess
import os
import sys

class CMakeBuild(build_ext):
    def run(self):
        src_dir = os.path.abspath(".")
        build_dir = os.path.join(src_dir, "build")
        install_dir = os.path.abspath("py_utilslib")

        os.makedirs(build_dir, exist_ok=True)
        subprocess.check_call(
            ["cmake", f"-DCMAKE_INSTALL_PREFIX={install_dir}", src_dir],
            cwd=build_dir
        )
        subprocess.check_call(["make", "-j4"], cwd=build_dir)
        super().run()

setup(
    name="utils-lib",
    version="1.0.0",
    packages=["py_utilslib"],
    package_data={"py_utilslib": ["*.pyi", "*.so", "*.pyd"]},
    cmdclass={"build_ext": CMakeBuild},
    zip_safe=False
)
from distutils.core import setup, Extension

module = Extension("MyModule", sources=["MyModule.c"])

setup(name="MyFibPackage", version="1.0", description="This is a package for MyModule.", ext_modules=[module])

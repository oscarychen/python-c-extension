#include <Python.h>
 
/**
 * The function implemented in C.
 */
int cFib(int n)
{
    if (n<2){
        return n;
    } else {
        return cFib(n-1)+cFib(n-2);
    }
};


/**
 * This function is called to translate arguments from Python.
 * The PyObject type is used as a pointer when we want to parse data between Python and C,
 * ie: static PyObject* myFunction(PyObject* self)
 * The PyArg_ParseTuple retrieves arguments from Python.
 * The Py_BuildValue turns a given value into Python object (PyObject pointer), see: https://docs.python.org/3/c-api/arg.html
 */
static PyObject* fib(PyObject* self, PyObject* args)
{ 
    int n;
    if (!PyArg_ParseTuple(args, "i", &n)){
        return NULL;
    }
    return Py_BuildValue("i", cFib(n));
};


/**
 * This function returns a string
 */
static PyObject* version(PyObject* self)
{
    return Py_BuildValue("s", "Version 1.0");
};


/**
 * This function demonstrates raising a Python exception from C function.
 * See list of standard exceptions: https://docs.python.org/3/c-api/exceptions.html#standard-exceptions
 * Note that you likely want to return NULL after setting a Python Exception.
 */
static PyObject* raise_exception(PyObject* self)
{
    PyErr_SetString(PyExc_Exception, "Oh no, something unexpected happened!");
    return NULL;
}


/**
 * This function demonstrates returning a Python None value.
 */
static PyObject* return_none(PyObject* self)
{
    return Py_BuildValue("");
}


/**
 * This function demonstrates another way of returning a Python None value.
 */
static PyObject* return_none_2(PyObject* self)
{
    Py_INCREF(Py_None);
    return Py_None;
}


/**
 * An array containing binding information for each function to be provided in this module.
 * Each entry contains the following:
 * - Python method name, 
 * - the function (you can optionally cast PyCFunction to ensure that this is a C function),
 * - function type (whether it takes args or not),
 * - a description/documentation for the function.
 * The last entry must be a null entry, ie: {NULL, NULL, 0, NULL} which marks end of array.
 */
static PyMethodDef myMethods[] = 
{
    {"fib", fib, METH_VARARGS, "Calculates the fibonacci numbers."},
    {"version", (PyCFunction)version, METH_NOARGS, "Returns the version."},
    {"raise_exception", (PyCFunction)raise_exception, METH_NOARGS, "Raises a Python exception."},
    {"return_none", (PyCFunction)return_none, METH_NOARGS, "Returns a Python None value."},
    {"return_none_2", (PyCFunction)return_none_2, METH_NOARGS, "Returns a Python None value."},
    {NULL, NULL, 0, NULL}
};


/**
 * Information about this module. 
 */
static struct PyModuleDef myModule = 
{
    PyModuleDef_HEAD_INIT,
    "MyModule", // name of the module
    "An example module to demonstrate Python C extension", // documentation of the module
    -1, // size of the preinterpreter state, -1 sets the module state to global
    myMethods // the PyMethodDef structure defined above
};


/**
 * Initializer function, this function is called when Python imports this module.
 * This function must be named in the form of PyInit_<module name>.
 * PyModule_Create creates the module from definition,
 * Initializes module and wraps the method pointers using module definition.
 */
PyMODINIT_FUNC PyInit_MyModule(void)
{
    return PyModule_Create(&myModule);
}
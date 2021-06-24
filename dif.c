#include <Python.h>
#include <math.h>

static PyObject *d_sin(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    return Py_BuildValue("d", cos(x));
}

static PyObject *d_cos(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    return Py_BuildValue("d", -sin(x));
}

static PyObject *d_ln(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    if (x <= 0) {
        PyErr_SetString(PyExc_ValueError, "The argument must be strictly greater than 0!");
        return NULL;
    }
    return Py_BuildValue("d", 1/x);
}

static PyObject *d_tan(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    if (cos(x) == 0) {
        PyErr_SetString(PyExc_ValueError, "The argument must not be pi/2 + pi*n!");
        return NULL;
    }
    return Py_BuildValue("d", 1/(pow(cos(x),2)));
}

static PyObject *d_ctan(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    if (sin(x) == 0) {
        PyErr_SetString(PyExc_ValueError, "The argument must not be pi*n!");
        return NULL;
    }
    return Py_BuildValue("d", -1/pow(sin(x),2));
}

static PyObject *d_arctan(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    return Py_BuildValue("d", 1/(1+pow(x,2)));
}

static PyObject *d_arcctan(PyObject *self, PyObject *args){
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)){
        return NULL;
    }
    return Py_BuildValue("d", -1/(1+pow(x,2)));
}

static PyObject *d_pow_a(PyObject *self, PyObject *args){
    double x,a;
    if (!PyArg_ParseTuple(args, "dd", &x,&a)){
        return NULL;
    }
    if (a <= 0) {
        PyErr_SetString(PyExc_ValueError, "The argument 'a' must be strictly greater than 0!");
        return NULL;
    }
    return Py_BuildValue("d", pow(a,x)*log(a));
}

static PyObject *d_log(PyObject *self, PyObject *args){
    double x,a;
    if (!PyArg_ParseTuple(args, "dd", &x,&a)){
        return NULL;
    }
    if (a <= 0 || a==1) {
        PyErr_SetString(PyExc_ValueError, "The argument 'a' must be strictly greater than 0 and 'a' must not be equal 1!");
        return NULL;
    }
    if (x <= 0) {
        PyErr_SetString(PyExc_ValueError, "The argument 'x' must be strictly greater than 0!");
        return NULL;
    }
    return Py_BuildValue("d", 1/(x*log(a)));
}

static PyObject *d_pow_x(PyObject *self, PyObject *args){
    double x,a;
    if (!PyArg_ParseTuple(args, "dd", &x,&a)){
        return NULL;
    }
    return Py_BuildValue("d", a*pow(x,a-1));
}

static PyMethodDef def_methods[] = {
    {"d_sin", d_sin, METH_VARARGS, "doc_sin"},
    {"d_cos", d_cos, METH_VARARGS, "doc_cos"},
    {"d_ln", d_ln, METH_VARARGS, "doc_ln"},
    {"d_arctan", d_arctan, METH_VARARGS, "doc_arctan"},
    {"d_arcctan", d_arcctan, METH_VARARGS, "doc_arcctan"},
    {"d_tan", d_tan, METH_VARARGS, "doc_tan"},
    {"d_ctan", d_ctan, METH_VARARGS, "doc_ctan"},
    {"d_pow_a", d_pow_a, METH_VARARGS, "doc_pow_a"},
    {"d_log", d_log, METH_VARARGS, "doc_log"},
    {"d_pow_x", d_pow_x, METH_VARARGS, "doc_pow_x"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef def_module = {
    PyModuleDef_HEAD_INIT,
    "dif",
    "doc_different",
    -1,
    def_methods,
    NULL,NULL,NULL
};

PyMODINIT_FUNC PyInit_dif(void)
{
    PyObject* m;
    m = PyModule_Create(&def_module);
    if (m == NULL)
        return NULL;
    return m;}


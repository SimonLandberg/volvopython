from cffi import FFI
ffibuilder = FFI()

ffibuilder.cdef("int addme(int a, int b);")
ffibuilder.cdef("int multiplyme(int a, int b);")
ffibuilder.cdef("int main();")
ffibuilder.set_source("python_and_c_interpreter",
"""
    #include "mw/mw_can.h"
    #include "os/types.h"
    #include "os/flags.h"
    #include "c_declarations.h"
""",
    sources=["main.c", "flags.c", "can1.c"],
    include_dirs=['os', 'mw'],
    libraries=['mw'],
    library_dirs=['mw'])

ffibuilder.compile()
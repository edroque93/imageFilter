#ifndef MACROS_HPP
#define MACROS_HPP

#include <stdio.h>

#define ERROR(error) { fprintf(stderr, "Error -> %s\n", error); exit(-1); }

#endif
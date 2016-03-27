#ifndef SETTER_H_INCLUDED
#define SETTER_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#include "mutex.h"
#include "thread.h"

typedef struct symbol_s{
    char * string;
    char symbol;
    mutex_t * mu;
}symbol_t;

typedef struct setter_s * setter_t;

void * symbolSetter(void * args);
setter_t setter_create(symbol_t* data);
void setter_remove(setter_t setter);

#endif // SETTER_H_INCLUDED

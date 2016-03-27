#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#include "mutex.h"
#include "thread.h"
#include "setter.h"


typedef struct reader_s * reader_t;

reader_t reader_create(symbol_t* data);
void reader_remove(reader_t reader);
void * digitReader(void * args);

#endif // READER_H_INCLUDED

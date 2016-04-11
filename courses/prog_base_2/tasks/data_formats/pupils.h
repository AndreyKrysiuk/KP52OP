#ifndef PUPILS_H_INCLUDED
#define PUPILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct pupils_s * pupils_t;

pupils_t pupils_new();
void pupils_remove(pupils_t self);
void pupils_print(pupils_t self);
int pupils_parseFromXML(pupils_t self, char * fileName);

#endif // PUPILS_H_INCLUDED

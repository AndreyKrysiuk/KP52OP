#ifndef PUPILS_H_INCLUDED
#define PUPILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#define WORD_LENGTH 30

typedef struct pupils_s * pupils_t;

#include "server.h"
pupils_t pupils_new();
void pupils_remove(pupils_t self);
void pupils_print(pupils_t self);
int pupils_parseFromXML(pupils_t self, char * fileName);

char * pupils_allPupilsToMessage(pupils_t self);
char * pupils_pupilByIdToMessage(pupils_t self, int id);

void pupils_deletePupil(pupils_t self, int id);
int pupils_checkID(pupils_t self, int id);

void pupils_changePupil(pupils_t self, int id, int newId, const char * name, const char * surname, const char * birthdate,
                         double score, int numberInList, const char * nameForm);

#endif // PUPILS_H_INCLUDED

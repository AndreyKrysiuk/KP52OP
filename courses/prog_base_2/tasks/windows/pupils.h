#ifndef PUPILS_H_INCLUDED
#define PUPILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 30

typedef struct pupil_s * pupil_t;

pupil_t pupil_new();
void pupil_remove(pupil_t self);
void pupil_randPupil(pupil_t pupil);

char * pupil_getName(pupil_t pupil);
char * pupil_getSurname(pupil_t pupil);
char * pupil_getBirthdate(pupil_t pupil);
char * pupil_getForm(pupil_t pupil);
int pupil_getNumber(pupil_t pupil);
double pupil_getScore(pupil_t pupil);


#endif // PUPILS_H_INCLUDED

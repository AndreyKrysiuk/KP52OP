#ifndef PUPILS_H_INCLUDED
#define PUPILS_H_INCLUDED

#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct pupils_s
{
    int id;
    char name[256];
    char surname[256];
    char birthDate[256];
    int form;
    double score;
} pupils_t;

#include "web.h"
#include "db_manager.h"

void pupil_print(pupils_t * pupil);
void pupils_printList(pupils_t * arr, int len);

char * pupils_getByIdToHTML(int id, db_t * db);
char * pupils_getAllToHTML(db_t * db);

char * pupils_getByIdToXML(db_t * db, int id);
char * pupils_getAllToXML(db_t * db);

void pupils_NodeXML(char * buffer, pupils_t * pupils);

#endif // PUPILS_H_INCLUDED

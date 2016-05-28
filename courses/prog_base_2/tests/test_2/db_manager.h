#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "sqlite3.h"
#include "list.h"
#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct db_s * db_t;
typedef struct pupils_s pupils_t;
typedef struct pupils_all_s * pupils_all_t;
db_t db_new(const char * dbFile);
void db_free(db_t self);

void db_getAllPupils(db_t self, pupils_all_t pupils);
void web_printPupilNodeXML(int id, char * name, char * surname, char * birthdate, int form, double score, char * buffer);

int db_countPupils(db_t self);
int pupils_all_getNum(pupils_all_t self);
pupils_all_t pupils_all_new();
char * pupils_all_msgAll(pupils_all_t self);
#endif // DB_MANAGER_H_INCLUDED

#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

typedef struct db_s db_t;

#include "pupils.h"

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

void db_getAllPupils(db_t * self, pupils_t * arr);

int db_countPupils(db_t * self);

int db_insertPupil(db_t * self, const char * name, const char * surname, const char * birthDate, int form, double score);
pupils_t * db_getPupilById(db_t * self, int id);
int db_checkID(db_t * self, int id);

char * db_getFiltrate(db_t * self, int count, int form, int state);
void db_deletePupil(db_t * self, int id);

#endif // DB_MANAGER_H_INCLUDED

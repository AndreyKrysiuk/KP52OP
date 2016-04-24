#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "pupils.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertPupil(db_t * self, pupils_t * pupils);
pupils_t* db_getPupilById(db_t * self, int id);
void db_updatePupil(db_t * self, pupils_t * pupils, int ID);
void db_deletePupil(db_t * self, int id);
void db_getAllPupils(db_t * self, pupils_t * arr);

int db_countPupils(db_t * self);

int db_getPupilsTask(db_t * self, int K, int P, pupils_t * arr);

#endif // DB_MANAGER_H_INCLUDED

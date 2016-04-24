#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>
#include "pupils.h"
#include "db_manager.h"

int main(void) {
    const char * dbFile = "pupils.db";
    pupils_t pupilsList[100];
    db_t * db = db_new(dbFile);

    int countAllPupils = db_countPupils(db);
    int numberPupils = 2;
    int form = 10;

    printf("Pupils total: %i\n\n", countAllPupils);
    int count = db_getPupilsTask(db, numberPupils, form, pupilsList);
    printf("%i pupils with max score from %i form:\n", numberPupils, form);
    pupils_printList(pupilsList, count);

    printf("Pupil with id 5\n");
    pupils_t * pupil = db_getPupilById(db, 5);
    pupil_print(pupil);


    pupils_t * newpupil = malloc(sizeof(struct pupils_s));
    strcpy(newpupil->name, "Igor");
    strcpy(newpupil->surname, "Lastochkin");
    strcpy(newpupil->birthDate, "1990-12-12");
    newpupil->score = 11.0;
    newpupil->form = 11;
    printf("New pupil id: %i\n", db_insertPupil(db, newpupil));


    printf("Count pupils before delete: %i\n",db_countPupils(db));
    db_deletePupil(db, 6);
    printf("Count pupils after delete: %i\n",db_countPupils(db));


    pupils_t * updated_pupil = malloc(sizeof(struct pupils_s));
    strcpy(updated_pupil->name, "Igor");
    strcpy(updated_pupil->surname, "Drinkin");
    strcpy(updated_pupil->birthDate, "1999-11-13");
    updated_pupil->score = 9.0;
    updated_pupil->form = 7;
    db_updatePupil(db, updated_pupil, 12);

    free(updated_pupil);
    free(pupil);
    free(newpupil);
    db_free(db);
    return 0;

}


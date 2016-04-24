#include <stdio.h>
#include <stdlib.h>

#include "pupils.h"


void pupil_print(pupils_t * pupil) {
    printf("Name: %s\nSurname: %s\nBirthDate: %s\nform: %i\nScore: %f\n\n",
        pupil->name, pupil->surname, pupil->birthDate, pupil->form, pupil->score);
}

void pupils_printList(pupils_t * arr, int len) {
    for (int i = 0; i < len; i++) {
        pupil_print(&arr[i]);
    }
}

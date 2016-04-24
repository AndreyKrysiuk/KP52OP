#ifndef PUPILS_H_INCLUDED
#define PUPILS_H_INCLUDED

typedef struct pupils_s{
    int id;
    char name[256];
    char surname[256];
    char birthDate[256];
    int form;
    double score;
}pupils_t;

void pupil_print(pupils_t * pupil);
void pupils_printList(pupils_t * arr, int len);



#endif // PUPILS_H_INCLUDED

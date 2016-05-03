#include "pupils.h"

typedef struct
{
    char nameForm[WORD_LENGTH];
    int numberInList;
} form_t;

struct pupil_s
{
    char name[WORD_LENGTH];
    char surname[WORD_LENGTH];
    char birthdate[WORD_LENGTH];
    double score;
    form_t form;
};

pupil_t pupil_new()
{
    pupil_t pupils = malloc(sizeof(struct pupil_s));
    return pupils;
}

void pupil_remove(pupil_t self)
{
    free(self);
    self = NULL;
}

void pupil_randPupil(pupil_t pupil)
{
    char * names[12] = {"Ivan", "Petya", "Andrey", "Dima", "Katya", "Olya", "Vlad", "Vova", "Glev", "Darya", "Inna", "Ira"};
    char * surnames[12] = {"Yaschenko", "Yashan", "Levoshko", "Varenich", "Krysyuk", "Litvinenko", "Salenko", "Samokhvalenko", "Fedorenko", "Dyachenko", "Kulichenko", "Malukha"};
    strcpy(pupil->name, names[rand()%12]);
    strcpy(pupil->surname, surnames[rand()%12]);
    sprintf(pupil->birthdate, "%i-%02i-%02i", 1980 + rand()%30, rand()%12 + 1, rand()%30 + 1);
    sprintf(pupil->form.nameForm, "%i-%c", rand()%11 + 1, rand()%6 + 65);
    pupil->score = (double)(rand())/RAND_MAX * 12;
    pupil->form.numberInList = rand()%40;
}

char * pupil_getName(pupil_t pupil)
{
    return pupil->name;
}

char * pupil_getSurname(pupil_t pupil)
{
    return pupil->surname;
}

char * pupil_getBirthdate(pupil_t pupil)
{
    return pupil->birthdate;
}


char * pupil_getForm(pupil_t pupil)
{
    return pupil->form.nameForm;
}

double pupil_getScore(pupil_t pupil)
{
    return pupil->score;
}

int pupil_getNumber(pupil_t pupil)
{
    return pupil->form.numberInList;
}


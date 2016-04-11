#include "pupils.h"

#define MAX_AMOUNT_PUPILS 20

typedef struct{
    char nameForm[30];
    int numberInList;
} form_t;

typedef struct pupil_s * pupil_t;

struct pupils_s{
    int amountPupils;
    pupil_t pupils[MAX_AMOUNT_PUPILS];
};


struct pupil_s{
    char name[30];
    char surname[30];
    char birthdate[30];
    double score;
    form_t form;
};

pupils_t pupils_new(){
    pupils_t pupils = malloc(sizeof(struct pupils_s));
    pupils->amountPupils = 0;
    return pupils;
}

void pupils_remove(pupils_t self){
    for(int i = 0; i < self->amountPupils; i++){
        free(self->pupils[i]);
        self->pupils[i] = NULL;
    }
    free(self);
    self = NULL;
}

void pupils_print(pupils_t self){
    for(int i = 0; i < self->amountPupils; i++){
        printf("Pupil:\n"
               "\tName: %s\n"
               "\tSurname: %s\n"
               "\tBirthdate: %s\n"
               "\tScore: %.2f\n"
               "\tForm name: %s\n"
               "\tNumber pupil in list: %i\n",
               self->pupils[i]->name,
               self->pupils[i]->surname,
               self->pupils[i]->birthdate,
               self->pupils[i]->score,
               self->pupils[i]->form.nameForm,
               self->pupils[i]->form.numberInList
               );
    }
}

int pupils_parseFromXML(pupils_t self, char* fileName){
	char line[1000];
    char text[10000] = "";
    FILE * fr = fopen(fileName, "r");
    while(fgets(line, 1000, fr)) {
        strcat(text, line);
    }
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml from memory");
        return 1;
    }
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ; xCur = xCur->next) {
        if (XML_ELEMENT_NODE == xCur->type) {
            self->pupils[self->amountPupils] = malloc(sizeof(struct pupil_s));
            for(xmlNode * xJ = xCur->children; NULL != xJ ; xJ = xJ->next) {
                if (XML_ELEMENT_NODE == xJ->type) {
                    if(strcmp(xJ->name, "form") == 0) {
                        xmlNode * xForm = xJ;
                        xmlNode * xNum = xForm->children->next;
                        char * nameForm = xmlGetProp(xForm, "nameForm");
                        strcpy(self->pupils[self->amountPupils]->form.nameForm, nameForm);
                        char * numberInlist = xmlNodeGetContent(xNum);
                        self->pupils[self->amountPupils]->form.numberInList = atoi(numberInlist);
                        continue;
                    } else if(strcmp(xJ->name, "name") == 0){
                        const char * name = xmlNodeGetContent(xJ);
                        strcpy(self->pupils[self->amountPupils]->name, name);
                    } else if(strcmp(xJ->name, "surname") == 0){
                        const char * surname = xmlNodeGetContent(xJ);
                        strcpy(self->pupils[self->amountPupils]->surname, surname);
                    } else if(strcmp(xJ->name, "birthdate") == 0){
                        const char * birthdate = xmlNodeGetContent(xJ);
                        strcpy(self->pupils[self->amountPupils]->birthdate, birthdate);
                    } else if(strcmp(xJ->name, "score") == 0){
                        const char * score = xmlNodeGetContent(xJ);
                        self->pupils[self->amountPupils]->score = atof(score);
                    }
                }
            }
            self->amountPupils++;
        }
    }
    fclose(fr);
    return 0;
}


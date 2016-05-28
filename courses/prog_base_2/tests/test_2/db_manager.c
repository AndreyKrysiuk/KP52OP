#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db_manager.h"

struct pupils_s{
    int id;
    char name[256];
    char surname[256];
    char birthDate[256];
    int form;
    double score;
};

struct pupils_all_s{
    list_t * pupils;
    int numPupils;
};


int pupils_all_getNum(pupils_all_t self){
    return self->numPupils;
}

struct db_s {
    sqlite3 * db;
};


pupils_all_t pupils_all_new(){
    pupils_all_t pupils_all = malloc(sizeof(struct pupils_all_s));
    pupils_all->pupils = list_new();
    return pupils_all;
}

db_t db_new(const char * dbFile) {
    db_t self = malloc(sizeof(struct db_s));
    self->db = NULL;
    int rc = sqlite3_open(dbFile, &(self->db));
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t self) {
    sqlite3_close(self->db);
    free(self);
}

static void _fillPupil(sqlite3_stmt * stmt, pupils_t * pupil) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    const unsigned char * birthdate = sqlite3_column_text(stmt, 3);
    int form = sqlite3_column_int(stmt, 4);
    double score = sqlite3_column_double(stmt, 5);
    pupil->id = id;
    strcpy(pupil->name, (const char *)name);
    strcpy(pupil->surname, (const char *)surname);
    strcpy(pupil->birthDate, (const char *)birthdate);
    pupil->form = form;
    pupil->score = score;
}




int db_countPupils(db_t self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM PUPILS;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void db_getAllPupils(db_t self, pupils_all_t pupils){
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM PUPILS";
    int count = 0;
    int rc = sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select pupils\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            pupils_t * newPupil = malloc(sizeof(struct pupils_s));
            _fillPupil(stmt, newPupil);
            list_push_back(pupils->pupils, newPupil);
            pupils->numPupils++;
            count++;
        }
    }
    sqlite3_finalize(stmt);
}



void web_printPupilNodeXML(pupils_t * pupils, char * buffer){

  	xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * studentNode = NULL;
	xmlNode * groupNode = NULL;
	char strBuf[100];

	doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "pupils");
	xmlDocSetRootElement(doc, rootNode);

	studentNode = xmlNewChild(rootNode, NULL, "pupil", NULL);
	sprintf(strBuf, "%i", pupils->id);
	xmlNewChild(studentNode, NULL, "id", strBuf);
	xmlNewChild(studentNode, NULL, "name", pupils->name);
	xmlNewChild(studentNode, NULL, "surname", pupils->surname);
	xmlNewChild(studentNode, NULL, "birthdate", pupils->birthDate);
	sprintf(strBuf, "%d", pupils->form);
	xmlNewChild(studentNode, NULL, "form", strBuf);
	sprintf(strBuf, "%.2f", pupils->score);
    xmlNewChild(studentNode, NULL, "score", strBuf);
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	strcpy(buffer, strstr((char *)bufferPtr->content, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")+strlen("<?xml version=\"1.0\" encoding=\"UTF-8\"?>")+1);
	xmlBufferFree(bufferPtr);

    xmlFreeDoc(doc);
	xmlCleanupParser();
}

char * pupils_all_msgAll(pupils_all_t self){

     char result[100000];
        char buff[10000];
        strcat(result, "<pupils>\n");
        for(int i = 0; i < self->numPupils; i++ ){
            web_printPupilNodeXML(list_get(self->pupils, i), buff);
            printf("%s", buff);
            sprintf(result, "%s\n", buff);
        }
        strcat(result, "</pupils>\n");
        return result;

}



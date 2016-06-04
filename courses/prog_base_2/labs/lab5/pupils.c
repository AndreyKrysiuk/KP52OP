#include <stdio.h>
#include <stdlib.h>

#include "pupils.h"

char * pupils_getByIdToHTML(int id, db_t * db)
{
    char * message = malloc(sizeof(char) * MSG_LENGTH);
    pupils_t * pupil = db_getPupilById(db, id);
    if(pupil == NULL)
    {
        return 0;
    }
    sprintf(message,
            "<!DOCTYPE html>"
            "<html>"
            "<head>"
            "<meta charset=\"UTF-8\">"
            "<meta http-equiv=\"refresh\" content=\"3\">"
            "<title>Pupil</title>"
            "</head>"
            "<body>"
            "<table border=\"1\"  width=\"75\%\">"
            "<tr>"
            "<th>ID</th>"
            "<th>First name</th>"
            "<th>Last name</th>"
            "<th>Birthdate</th>"
            "<th>Form</th>"
            "<th>Score</th>"
            "</tr>"
            "<tr>"
            "<td>%i</td>"
            "<td>%s</td>"
            "<td>%s</td>"
            "<td>%s</td>"
            "<td>%i</td>"
            "<td>%.2f</td>"
            "</tr>"
            "</table>"
            "<p> <a href=\"http://127.0.0.1:5000/pupils\"> Back </a></p>"
            "<p> <a href= \"#\" onclick=\"doDelete()\"> Delete pupil </a></p>"
            "<script>"
            "function doDelete() {"
            "var xhttp = new XMLHttpRequest();"
            "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/pupils/%i\", true);"
            "xhttp.send();}"
            "</script>"
            "</body>"
            "</html>",
            pupil->id,
            pupil->name,
            pupil->surname,
            pupil->birthDate,
            pupil->form,
            pupil->score,
            pupil->id);
    return message;
}


char * pupils_getAllToHTML(db_t * db)
{
    char * message = malloc(sizeof(char) * 10 * MSG_LENGTH);
    char * buff = malloc(sizeof(char) * MSG_LENGTH);
    int count = db_countPupils(db);
    pupils_t pupils[count];
    db_getAllPupils(db, pupils);
    sprintf(message, "");
    strcat(message,
           "<!DOCTYPE html>"
           "<html>"
           "<head>"
           "<meta charset=\"UTF-8\">"
           "<title>Pupils</title>"
           "</head>"
           "<body>"
           "<table border=\"1\"  width=\"25\%\">"
           "<tr>"
           "<th>ID</th>"
           "<th>Name</th>"
           "</tr>");
    for(int i = 0; i < count; i++)
    {
        sprintf(buff,
                "<tr>"
                "<td>%i</td>"
                "<td> <a href=\"http://127.0.0.1:5000/pupils/%i\">%s %s</a> </td>"
                "</tr>",
                pupils[i].id,
                pupils[i].id,
                pupils[i].name,
                pupils[i].surname);
        strcat(message, buff);
    }
    strcat(message,
           "<p> <a href=\"http://127.0.0.1:5000\"> Back </a> </p>"
           "<p> <a href=\"http://127.0.0.1:5000/new-pupil\"> New pupil </a> </p>"
           "</table>"
           "</body>"
           "</html>");
    return message;
}

char * pupils_getByIdToXML(db_t * db, int id)
{
    pupils_t * pupil = db_getPupilById(db, id);
    char * message = malloc(sizeof(char) * MSG_LENGTH);
    pupils_NodeXML(message, pupil);
    return message;
}

char * pupils_getAllToXML(db_t * db)
{

    int count = db_countPupils(db);
    pupils_t pupils[count];
    db_getAllPupils(db, pupils);
    char message[MSG_LENGTH] = "<pupils>\n";
    char buff[MSG_LENGTH];
    char * tmpBuff = malloc(sizeof(char) * MSG_LENGTH);
    for(int i = 0; i < count; i++)
    {
        pupils_NodeXML(tmpBuff, &pupils[i]);
        sprintf(buff, "%s", tmpBuff);
        strcat(message, buff);
    }
    strcat(message, "</pupils>\n");
    return message;
}



void pupils_NodeXML(char * buffer, pupils_t * pupils)
{

    xmlDoc * doc = NULL;
    xmlNode * rootNode = NULL;
    xmlNode * studentNode = NULL;
    char strBuf[100];

    doc = xmlNewDoc("1.0");
    rootNode = xmlNewNode(NULL, "pupils");
    xmlDocSetRootElement(doc, rootNode);

    studentNode = xmlNewChild(rootNode, NULL, "pupil", NULL);
    sprintf(strBuf, "%i", pupils->id);
    xmlNewChild(studentNode, NULL, "id", strBuf);
    xmlNewChild(studentNode, NULL, "name", pupils->name);
    xmlNewChild(studentNode, NULL, "surname", pupils->surname);
    xmlNewChild(studentNode, NULL, "birthDate", pupils->birthDate);
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



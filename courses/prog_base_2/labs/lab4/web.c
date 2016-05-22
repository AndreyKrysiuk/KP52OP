#include "web.h"

struct keyvalue_s{
    char key[256];
    char value[256];
};

struct http_request_s{
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
};


static char * readHTML(char * nameFile){
         char page[2000];
         FILE* finput = fopen(nameFile, "r");
         int len = fread(page, sizeof(char), sizeof(page)/sizeof(char), finput);
         page[len] = '\0';
         fclose(finput);
         return page;
}

static void sendErrorMessageHTML(char * code, socket_t * clientSocket){
    char result_msg[MSG_LENGTH];
    sprintf(result_msg,
            "<!DOCTYPE html>"
            "<html>"
            "<head>"
            "<meta charset=\"UTF-8\">"
            "<title>Error</title>"
            "</head>"
            "<body>"
            "<h1> %s </h1>"
            "<p> <a href=\"http://127.0.0.1:5000/pupils\"> Back to menu</a></p>"
            "</body>"
            "</html>",
            code);
    socket_write_string(clientSocket, result_msg);
}

static void sendErrorMessageXML(char * code, socket_t * clientSocket){
     char result_msg[MSG_LENGTH];
    sprintf(result_msg,
            "<message>\n"
            "\t<status>Error</status>\n"
            "\t<text>%s</text>\n"
            "</message>\n",
            code);
    socket_write_string(clientSocket, result_msg);
}

static int checkInputData_HTMLresponse(socket_t * clientSocket, char * result, char * stName, char * stSurname, char* stBirthdate, char * stNameForm, int stNumberInList, double stScore){
    if(strlen(stName) == 0 || strlen(stName) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect name", clientSocket);
    else if(strlen(stSurname) == 0 || strlen(stSurname) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect Surname", clientSocket);
    else if(strlen(stBirthdate) == 0 || strlen(stBirthdate) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect Date", clientSocket);
    else if(strlen(stNameForm) == 0 || strlen(stNameForm) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect Form", clientSocket);
    else if(stScore < 0 || stScore > 12.0)
        sendErrorMessageHTML("Incorrect Score", clientSocket);
    else if(stNumberInList < 0 || stNumberInList > 50)
        sendErrorMessageHTML("Incorrect Number", clientSocket);
    else return 0;
    return 1;
}

static int checkInputData_XMLresponse(socket_t * clientSocket, char * result, char * stName, char * stSurname, char* stBirthdate, char * stNameForm, int stNumberInList, double stScore){
    if(strlen(stName) == 0 || strlen(stName) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect name", clientSocket);
    else if(strlen(stSurname) == 0 || strlen(stSurname) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect Surname", clientSocket);
    else if(strlen(stBirthdate) == 0 || strlen(stBirthdate) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect Date", clientSocket);
    else if(strlen(stNameForm) == 0 || strlen(stNameForm) > WORD_LENGTH)
        sendErrorMessageHTML("Incorrect Form", clientSocket);
    else if(stScore < 0 || stScore > 12.0)
        sendErrorMessageHTML("Incorrect Score", clientSocket);
    else if(stNumberInList < 0 || stNumberInList > 50)
        sendErrorMessageHTML("Incorrect Number", clientSocket);
    else return 0;
    return 1;
}

http_request_t
http_request_parse(const char * const request) {
    http_request_t req;
    req.form = NULL;
    req.formLength = 0;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    // parse form data
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0) {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr) {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char *
http_request_getArg(http_request_t * self, const char * key) {
    for (int i = 0; i < self->formLength; i++) {
        if (strcmp(self->form[i].key, key) == 0) {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self) {
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}

void http_request_startServer(pupils_t pupils){
    lib_init();
    socket_t * serverSocket = socket_new();
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);
    while(1){
        puts("Waiting for connections");
        socket_t * clientSocket = socket_accept(serverSocket);
        puts("New client");
        char buff[BUFFER_LENGTH];
        int readLength = socket_read(clientSocket, buff, BUFFER_LENGTH);
        if(readLength == 0){
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }

        printf("Got Request:\n---------------\n%s\n----------------\n", buff);

        http_request_t req = http_request_parse(buff);

        printf("Method: %s\nURI: %s\n", req.method, req.uri);
        puts("Data:");
        for(int i = 0; i < req.formLength; i++){
            char * kvStr = keyvalue_toString(&req.form[i]);
            printf("\t%s\n", kvStr);
            free(kvStr);
        }
        http_request_chooseMethod(req, clientSocket, pupils);
        socket_close(clientSocket);
        socket_free(clientSocket);
    }
    socket_close(serverSocket);
    socket_free(serverSocket);
    lib_free();
}

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, pupils_t pupils){
    if(strcmp(req.uri, "/") == 0)
        {
            socket_write_string(clientSocket, readHTML("hello.html"));
    }
    else if(strcmp(req.uri, "/new-pupil") == 0)
        {
            if(strcmp(req.method, "GET") == 0)
            {
                socket_write_string(clientSocket, readHTML("webpage.html"));
            }
            else if(strcmp(req.method, "POST") == 0)
            {
                char result[MSG_LENGTH];
                const char * stName = http_request_getArg(&req, "name");
                const char * stSurname = http_request_getArg(&req, "surname");
                const char * stBirthdate = http_request_getArg(&req, "birthdate");
                const char * stNameForm = http_request_getArg(&req, "nameForm");
                int stNumberInList = atoi(http_request_getArg(&req, "numberInList"));
                int stId = 0;
                while(!pupils_checkID(pupils, stId)){
                    stId++;
                    }
                double stScore = atof(http_request_getArg(&req, "score"));
                if(checkInputData_HTMLresponse(clientSocket, result, stName,
                    stSurname, stBirthdate, stNameForm, stNumberInList, stScore)) return;
                else{
                    pupils_newPupil(pupils, stId, stName, stSurname, stBirthdate,
                                    stScore, stNumberInList, stNameForm);
                    printf("New:\n"
                            "<pupil>\n"
                            "\t<id>%i</id>\n"
                            "\t<name>%s</name>\n"
                            "\t<surname>%s</surname>\n"
                            "\t<birthdate>%s</birthdate>\n"
                            "\t<form nameForm=\"%s\">\n"
                            "\t\t<numberInList>%i</numberInList>\n"
                            "\t</form>\n"
                            "\t<score>%.2f</score>\n"
                            "</pupil>\n\n",
                            stId, stName, stSurname,
                            stBirthdate, stNameForm, stNumberInList, stScore);
                    sprintf(result,
                            "HTTP/1.1 200 OK\n"
                            "Content-length: %zu\n"
                            "Content-type: text/html\n"
                            "\n"
                            "%s\0",
                            strlen(pupils_PupilToHTMLMessage(pupils, stId)), (pupils_PupilToHTMLMessage(pupils, stId)));
                    socket_write_string(clientSocket, result);
                    }
            }
        }
    else if (strcmp(req.uri, "/pupils/") == 0) sendErrorMessageHTML("404 NOT FOUND", clientSocket);
    else if (strcmp(req.uri, "/pupils") > 0)
        {
            int id = atoi(strtok(req.uri, "/pupils"));
            if(pupils_checkID(pupils, id) == 0)
                {
                    if(strcmp(req.method, "GET") == 0)
                    {
                        if(pupils_PupilToHTMLMessage(pupils, id) != 0)
                        {
                            char result[BUFFER_LENGTH];
                            sprintf(result,
                                        "HTTP/1.1 200 OK\n"
                                        "Content-length: %zu\n"
                                        "Content-type: text/html\n"
                                        "\n"
                                        "%s\0",
                                        strlen(pupils_PupilToHTMLMessage(pupils, id)),
                                        pupils_PupilToHTMLMessage(pupils, id));
                            socket_write_string(clientSocket, result);
                        }
                    }
                    else if(strcmp(req.method, "DELETE") == 0)
                    {
                        pupils_deletePupil(pupils, id);
                        socket_write_string(clientSocket, readHTML("deleted.html"));
                        return;
                    }
                }
                else
                {
                    char result_msg[200];
                    sprintf(result_msg, "PUPIL WITH ID %i NOT FOUND", id);
                    sendErrorMessageHTML(result_msg, clientSocket);
                }
        }
    else if (strcmp(req.uri, "/pupils") == 0)
        {
            if(strcmp(req.method, "GET") == 0)
            {
                char result[BUFFER_LENGTH];
                sprintf(result,
                    "HTTP/1.1 200 OK\n"
                    "Content-length: %zu\n"
                    "Content-type: text/html\n"
                    "\n"
                    "%s\0",
                    (int)strlen(pupils_AlltoHTMLMessage(pupils)), pupils_AlltoHTMLMessage(pupils));
                socket_write_string(clientSocket, result);
            }
            else sendErrorMessageHTML("NOT ALLOWED", clientSocket);
        }
        else if (strcmp(req.uri, "/api/pupils/") == 0)
        {
            sendErrorMessageXML("NOT FOUND", clientSocket);
        }
    else if (strcmp(req.uri, "/api/pupils") > 0)
        {
            int id = atoi(strtok(req.uri, "/api/pupils"));
            if(pupils_checkID(pupils, id) == 0)
                {
                    if(strcmp(req.method, "GET") == 0)
                    {
                        if(pupils_PupilToXMLMessage(pupils, id) != 0)
                        {
                            char result[BUFFER_LENGTH];
                            sprintf(result,
                                    "HTTP/1.1 200 OK\n"
                                    "Content-length: %zu\n"
                                    "Content-type: application/xml\n"
                                    "\n"
                                    "%s\0",
                                    strlen(pupils_PupilToXMLMessage(pupils, id)),
                                    pupils_PupilToXMLMessage(pupils, id));
                            socket_write_string(clientSocket, result);
                        }
                    }
                else if(strcmp(req.method, "DELETE") == 0)
                    {
                        pupils_deletePupil(pupils, id);
                        char result_msg[MSG_LENGTH];
                        sprintf(result_msg,
                                "<message>\n"
                                "\t<status>ok</status>\n"
                                "\t<text>Pupil (id%i) has been deleted</text>\n"
                                "</message>\n", id);
                        socket_write_string(clientSocket, result_msg);
                    }
                }
                    else{
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,"Pupil (id%i) not found", id);
                    sendErrorMessageXML(result_msg, clientSocket);
                }
        }
    else if (strcmp(req.uri, "/api/pupils") == 0)
        {
            if(strcmp(req.method, "GET") == 0)
            {
                char result[10000];
                sprintf(result,
                        "HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0",
                        strlen(pupils_AlltoXMLMessage(pupils)), pupils_AlltoXMLMessage(pupils));
                socket_write_string(clientSocket, result);
            }
            else if(strcmp(req.method, "POST") == 0)
                {
                    char result[MSG_LENGTH];
                    const char * stName = http_request_getArg(&req, "name");
                    const char * stSurname = http_request_getArg(&req, "surname");
                    const char * stBirthdate = http_request_getArg(&req, "birthdate");
                    const char * stNameForm = http_request_getArg(&req, "nameForm");
                    int stNumberInList = atoi(http_request_getArg(&req, "numberInList"));
                    int stId = 0;
                    while(!pupils_checkID(pupils, stId)){
                        stId++;
                    }
                    double stScore = atof(http_request_getArg(&req, "score"));
                    if(checkInputData_XMLresponse(clientSocket, result, stName,
                        stSurname, stBirthdate, stNameForm, stNumberInList, stScore)) return;
                    else {
                        pupils_newPupil(pupils, stId, stName, stSurname, stBirthdate,
                                        stScore, stNumberInList, stNameForm);
                        socket_write_string(clientSocket, pupils_PupilToXMLMessage(pupils, stId));
                        char res[MSG_LENGTH];
                        sprintf(res,"<pupil>\n"
                                    "\t<id>%i</id>\n"
                                    "\t<name>%s</name>\n"
                                    "\t<surname>%s</surname>\n"
                                    "\t<birthdate>%s</birthdate>\n"
                                    "\t<form nameForm=\"%s\">\n"
                                    "\t\t<numberInList>%i</numberInList>\n"
                                    "\t</form>\n"
                                    "\t<score>%.2f</score>\n"
                                    "</pupil>\n\n",
                                    stId, stName, stSurname,
                                    stBirthdate, stNameForm, stNumberInList, stScore);
                        sprintf(result,
                                    "HTTP/1.1 200 OK\n"
                                    "Content-length: %zu\n"
                                    "Content-type: application/xml\n"
                                    "\n"
                                    "%s\0",
                                    strlen(res), res);
                        socket_write_string(clientSocket, result);
                    }
                }
            else sendErrorMessageXML("NOL ALLOWED", clientSocket);
        }
    else sendErrorMessageHTML("404 NOT FOUND", clientSocket);
}



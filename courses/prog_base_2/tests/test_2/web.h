#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


#include <libxml/parser.h>
#include <libxml/tree.h>

#include "socket.h"
#include "db_manager.h"
//#include "curl.h"

#define BUFFER_LENGTH 100000
#define MSG_LENGTH 10000

typedef struct keyvalue_s keyvalue_t;
typedef struct http_request_s http_request_t;

http_request_t
http_request_parse(const char * const request);

const char *
http_request_getArg(http_request_t * self, const char * key);

const char *
keyvalue_toString(keyvalue_t * self);


void web_printInfoNodeXML();


list_t * web_textToList(char * text);
char * web_listToHTML(list_t * list);
void http_request_startServer(pupils_all_t pupils);
void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, pupils_all_t pupils);

#endif // SERVER_H_INCLUDED

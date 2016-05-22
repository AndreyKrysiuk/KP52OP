#include <stdio.h>
#include <stdlib.h>

#include "web.h"
#include "pupils.h"
#include "socket.h"

int main(){
    char * fileName = "pupils.xml";
    pupils_t pupils = pupils_new();
    pupils_parseFromXML(pupils, fileName);
    http_request_startServer(pupils);
    pupils_remove(pupils);
}

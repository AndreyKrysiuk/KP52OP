#include <stdio.h>
#include <stdlib.h>

#include "socket.h"
#include "pupils.h"
#include "server.h"

int main()
{
    char * fileName = "pupils.xml";
    pupils_t pupils = pupils_new();
    pupils_parseFromXML(pupils, fileName);
    http_request_startServer(pupils);
    pupils_remove(pupils);
    return 0;
}



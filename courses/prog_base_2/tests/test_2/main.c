#include <stdio.h>
#include <stdlib.h>

#include "db_manager.h"
#include "web.h"

int main()
{
    db_t database = db_new("pupils.db");
    pupils_all_t pupils = pupils_all_new();
    db_getAllPupils(database, pupils);
    //http_request_startServer(pupils);
    return 0;
}

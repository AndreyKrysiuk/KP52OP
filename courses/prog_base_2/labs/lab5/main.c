#include <stdio.h>
#include <stdlib.h>

#include "db_manager.h"

int main()
{
    char * dbName = "pupils.db";
    db_t * db = db_new(dbName);
    http_request_startServer(db);
    db_free(db);
    return 0;
}

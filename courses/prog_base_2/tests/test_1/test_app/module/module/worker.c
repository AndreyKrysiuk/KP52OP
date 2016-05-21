#include "worker.h"

struct worker_s{
    char name[100];
    STATUS status;
};

worker_t worker_new(char * name, STATUS status){
    worker_t worker = malloc(sizeof(struct worker_s));
    strcpy(worker->name, name);
    worker->status = status;
    return worker;
}

char * worker_getName(worker_t worker){
    return worker->name;
}

STATUS worker_getStatus(worker_t worker){
    return worker->status;
}

void worker_setStatus(worker_t worker, STATUS status){
    worker->status = status;
}

void worker_delete(worker_t worker){
    free(worker);
}

#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

typedef enum {ALLOWED, BLOCKED} STATUS;
typedef struct worker_s* worker_t;

worker_t worker_new(char * name, STATUS status);

char * worker_getName(worker_t worker);
STATUS worker_getStatus(worker_t worker);

void worker_setStatus(worker_t worker, STATUS status);
void worker_delete(worker_t worker);
#endif // WORKER_H_INCLUDED

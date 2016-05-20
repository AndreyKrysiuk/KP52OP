#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "events.h"
#include <windows.h>

typedef struct helper_s * helper_t;

helper_t helper_new();

void helper_delete(helper_t helper);

int helper_getNumEvents(helper_t helper);
int helper_addEvent(helper_t helper, event_t event);
void helper_reminder(helper_t helper);


#endif // HELPER_H_INCLUDED

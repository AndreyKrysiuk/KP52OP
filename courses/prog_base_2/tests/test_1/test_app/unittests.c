#include <stdio.h>
#include <stdarg.h>

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "turniket.h"


void reaction(worker_t worker, event_t event);

static void getEventsForLastHour_NoOne_countZero(void ** state){
    callback rc = reaction;
    turniket_t turniket = turniket_create(rc);
    worker_t worker1 = worker_new("Andrey Krysyuk", ALLOWED);
    worker_t worker2 = worker_new("Olga Yashan", ALLOWED);
    event_t event1 = event_new(worker1, 1000, INSIDE);
    event_t event2 = event_new(worker2, 1200, INSIDE);

    turniket_addEvent(turniket, event1);
    turniket_addEvent(turniket, event2);
    list_t * forLastHour = list_new();
    int count = turniket_getEventsForLastHour(turniket, forLastHour, 1500);
    assert_int_equal(count , 0);
    turniket_delete(turniket);
    event_delete(event1);
    event_delete(event2);
    worker_delete(worker1);
    worker_delete(worker2);
}


static void getEventsForLastHour_fourEvents_countFour(void ** state){
    callback rc = reaction;
    turniket_t turniket = turniket_create(rc);
    worker_t worker1 = worker_new("Andrey Krysyuk", ALLOWED);
    worker_t worker2 = worker_new("Olga Yashan", ALLOWED);
    event_t event1 = event_new(worker1, 1230, INSIDE);
    event_t event2 = event_new(worker2, 1200, INSIDE);
    event_t event3 = event_new(worker1, 1250, OUTSIDE);
    event_t event4 = event_new(worker2, 1255, OUTSIDE);
    turniket_addEvent(turniket, event1);
    turniket_addEvent(turniket, event2);
    turniket_addEvent(turniket, event3);
    turniket_addEvent(turniket, event4);
    list_t * forLastHour = list_new();
    int count = turniket_getEventsForLastHour(turniket, forLastHour, 1260);
    assert_int_equal(count , 4);
    turniket_delete(turniket);
    event_delete(event1);
    event_delete(event2);
    event_delete(event3);
    event_delete(event4);
}


static void getEventsForLastHour_fourEvents_countTwo(void ** state){
    callback rc = reaction;
    turniket_t turniket = turniket_create(rc);
    worker_t worker1 = worker_new("Andrey Krysyuk", ALLOWED);
    worker_t worker2 = worker_new("Olga Yashan", ALLOWED);
    event_t event1 = event_new(worker1, 1230, INSIDE);
    event_t event2 = event_new(worker2, 1200, INSIDE);
    event_t event3 = event_new(worker1, 1250, OUTSIDE);
    event_t event4 = event_new(worker2, 1255, OUTSIDE);
    turniket_addEvent(turniket, event1);
    turniket_addEvent(turniket, event2);
    turniket_addEvent(turniket, event3);
    turniket_addEvent(turniket, event4);
    list_t * forLastHour = list_new();
    int count = turniket_getEventsForLastHour(turniket, forLastHour, 1300);
    assert_int_equal(count , 2);
    turniket_delete(turniket);
    event_delete(event1);
    event_delete(event2);
    event_delete(event3);
    event_delete(event4);
}


int run_unit_tests(){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(getEventsForLastHour_NoOne_countZero),
        cmocka_unit_test(getEventsForLastHour_fourEvents_countFour),
        cmocka_unit_test(getEventsForLastHour_fourEvents_countTwo)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

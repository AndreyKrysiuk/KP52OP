#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "user.h"
#include "callbacks.h"
#include "events.h"
#include "helper.h"


static void events_addFollower__fiveFollowers__numFollowersFive(void ** state){
    callback rc1 = reaction1;
    callback rc2 = reaction2;
    user_t user1 = user_new("Rob Stark", rc1);
    char * description = "Red wedding";
    char * names[5] = {"Frey", "Lannister", "Karstark", "Greyjoy", "Baratheon"};
    event_t event = event_new(user1, description, 10);
    user_t user[5];
    for(int i = 0; i < 5; i++){
        user[i] = user_new(names[i], rc2);
        event_addFollower(event, user[i]);
    }
    assert_int_equal(event_getNumFollowers(event), 5);
}


int run_unit_tests(){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(events_addFollower__fiveFollowers__numFollowersFive)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

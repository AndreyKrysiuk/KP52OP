#include <stdio.h>
#include <stdlib.h>

#include "user.h"
#include "callbacks.h"
#include "events.h"
#include "helper.h"

int main()
{
    callback cb1 = reaction1;
    callback cb2 = reaction2;
    callback cb3 = reaction3;
    user_t user1 = user_new("Andrey", cb1);
    user_t user2 = user_new("Darya", cb2);
    user_t user3 = user_new("Vova", cb1);
    user_t user4 = user_new("Gleb", cb3);

    char * descr1 = "Skillet 15.05.16\n";
    char * descr2 = "Buy t-short with logo before concert Skillet\n";

    event_t event1 = event_new(user1, descr1, 15);
    event_t event2 = event_new(user2, descr2, 7);

    event_addFollower(event1, user2);
    event_addFollower(event1, user3);
    event_addFollower(event1, user4);

    helper_t helper1 = helper_new();

    helper_addEvent(helper1, event1);
    helper_addEvent(helper1, event2);

    helper_reminder(helper1);

    user_delete(user1);
    user_delete(user2);
    user_delete(user3);
    user_delete(user4);

    helper_delete(helper1);
    event_delete(event2);
    event_delete(event1);

    printf("========================UNIT TESTS===========================\n");

    run_unit_tests();
    return 0;
}

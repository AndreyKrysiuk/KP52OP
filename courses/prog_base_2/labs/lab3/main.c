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
    user_t user2 = user_new("Ruslan", cb2);
    user_t user3 = user_new("Vova", cb1);
    user_t user4 = user_new("Gleb", cb3);

    char * descr1 = "skillet 15.05.16\n";
    char * descr2 = "Test for students next week\n";

    /*cb1(user1, descr1);
    cb2(user2, descr2);*/

    event_t event1 = event_new(user1, descr1, 10);
    event_t event2 = event_new(user2, descr2, 30);

   /*printf("Event 1 from user %s: %s", event_getCreatorName(event1), event_getDescription(event1));
    printf("Event 2 from user %s: %s", event_getCreatorName(event2), event_getDescription(event2));*/

    event_addFollower(event1, user2);
    event_addFollower(event1, user3);
    event_addFollower(event1, user4);
    printf("%i\n", event_getNumFollowers(event1));

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

    run_unit_tests();
    return 0;
}

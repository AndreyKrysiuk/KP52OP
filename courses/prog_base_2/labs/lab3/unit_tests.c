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

static void event_new__invalidData__returnNULL(void ** state){
    callback rc1 = reaction1;
    user_t user1 = user_new("Rob Stark", rc1);
    char * description = "Red wedding";
    event_t event1 = event_new(user1, "", 10);
    assert_ptr_equal(event1, NULL);
    event_t event2 = event_new(NULL, description, 10);
    assert_ptr_equal(event2, NULL);
    event_t event3 = event_new(user1, description, -11234);
    assert_ptr_equal(event3, NULL);
    user_delete(user1);
}

static void event_getFollowerName__invalidIndex__errorIncorectData(void ** state){
    callback rc1 = reaction1;
    user_t user1 = user_new("Rob Stark", rc1);
    char * description = "Red wedding";
    event_t event1 = event_new(user1, description, 10);
    event_getFollowerName(event1, 0);
    assert_int_equal(event_getStatus(event1), ERROR_INCORECT_DATA);
    event_delete(event1);
    user_delete(user1);
}

static void event_getFollowerName__correctValue__returnEqualValue(void ** state){
    callback rc1 = reaction1;
    callback rc2 = reaction2;
    user_t user1 = user_new("Rob Stark", rc1);
    user_t user2 = user_new("Jhon Snow", rc2);
    char * description = "Red wedding";
    event_t event1 = event_new(user1, description, 10);
    event_addFollower(event1, user2);
    assert_string_equal("Jhon Snow",  event_getFollowerName(event1, 0));
    assert_int_equal(event_getStatus(event1), STATUS_OK);
    event_delete(event1);
    user_delete(user1);
    user_delete(user2);
}



static void event_addFollower__nullPointer__errorNullPointer(void ** state){
    callback rc1 = reaction1;
    user_t user1 = user_new("Rob Stark", rc1);
    char * description = "Red wedding";
    event_t event = event_new(user1, description, 10);
    event_addFollower(event, NULL);
    assert_int_equal(event_getStatus(event), ERROR_NULL_POINTER);
    user_delete(user1);
    event_delete(event);
}

static void event_addFollower__fiveFollowers__numFollowersFive(void ** state){
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
    assert_int_equal(event_getStatus(event), STATUS_OK);
    user_delete(user1);
    for(int i = 0; i < 5; i++){
        user_delete(user[i]);
    }
    event_delete(event);
}

static void event_getFollower__invalidIndex__returnNullAndErrorIncorectData(void ** state){
    callback rc1 = reaction1;
    user_t user = user_new("Rob Stark", rc1);
    char * description = "Red wedding";
    event_t event = event_new(user, description, 10);

    assert_ptr_equal(event_getFollower(event, 1000), NULL);
    assert_int_equal(event_getStatus(event), ERROR_INCORECT_DATA);

    user_delete(user);
    event_delete(event);
}

static void event_getCreatorName__correctData__equalValue(void ** state){
    callback rc1 = reaction1;
    char * name = "Rob Stark";
    user_t user = user_new(name, rc1);
    char * description = "Red wedding";
    event_t event = event_new(user, description, 10);
    assert_string_equal(event_getCreatorName(event), name);
    assert_int_equal(event_getStatus(event), STATUS_OK);

    user_delete(user);
    event_delete(event);
}

static void event_getFollower__correctData__equalPointer(void ** state){
    callback rc1 = reaction1;
    user_t user = user_new("Rob Stark", rc1);
    user_t follower = user_new("Jhon Snow", rc1);
    char * description = "Red wedding";
    event_t event = event_new(user, description, 10);
    event_addFollower(event, follower);
    assert_ptr_equal(event_getFollower(event, 0), follower);

    user_delete(follower);
    user_delete(user);
    event_delete(event);

}


int run_unit_tests(){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(event_addFollower__fiveFollowers__numFollowersFive),
        cmocka_unit_test(event_addFollower__nullPointer__errorNullPointer),
        cmocka_unit_test(event_new__invalidData__returnNULL),
        cmocka_unit_test(event_getFollowerName__invalidIndex__errorIncorectData),
        cmocka_unit_test(event_getFollowerName__correctValue__returnEqualValue),
        cmocka_unit_test(event_getFollower__invalidIndex__returnNullAndErrorIncorectData),
        cmocka_unit_test(event_getFollower__correctData__equalPointer),
        cmocka_unit_test(event_getCreatorName__correctData__equalValue)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

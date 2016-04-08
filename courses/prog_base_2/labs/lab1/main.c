#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "core.h"
#include "posts.h"
#include "car.h"


static void posts_new__void__ZeroCountPosts(void ** state){
    posts_t posts = posts_new();
    assert_int_equal(posts_getAmountPosts(posts), 0);
    assert_int_equal(posts_getErrorCode(posts), 0);
    posts_remove(posts);
}
static void posts_addNewPost__tenNewPosts__CountPostsTen(void ** state){
    posts_t posts = posts_new();
    for(int i = 0; i < 10; i++){
        posts_addNewPost(posts, (i+1)*10);
    }
    for(int i = 0; i < 10; i++){
        assert_int_equal(posts_getPostMaxSpeed(posts, i), (i+1)*10);
    }
    assert_int_equal(posts_getAmountPosts(posts), 10);
    assert_int_equal(posts_getErrorCode(posts), 0);
    posts_remove(posts);
}

static void core_new__void__ZeroCountViolators(void ** state){
    core_t core = core_new();
    assert_int_equal(core_getAmountViolators(core), 0);
    assert_int_equal(core_getErrorStatus(core), 0);
    core_remove(core);
}

static void core_new__fiveCarsOnTwoPosts__countViolatorsThree(void ** state){
    core_t core = core_new();
    car_t car[5];
    for(int i = 0; i < 5; i++){
        car[i] = car_new(90 + i*10);
        assert_non_null(car[i]);
        assert_int_equal(car_getSpeed(car[i]), 90 + i*10);
    }
    posts_t posts = posts_new();
    posts_addNewPost(posts, 120);
    posts_addNewPost(posts, 90);
    posts_checkViolator(posts, 0, car[0], core);
    posts_checkViolator(posts, 1, car[1], core);
    posts_checkViolator(posts, 1, car[2], core);
    posts_checkViolator(posts, 0, car[3], core);
    posts_checkViolator(posts, 0, car[4], core);
    assert_int_equal(core_getAmountViolators(core), 3);
    assert_int_equal(core_getErrorStatus(core), 0);
    for(int i = 0; i < 5; i++){
        car_remove(car[i]);
    }
    posts_remove(posts);
    core_remove(core);
}

static void car_new__invalidSpeed__NULL(void **state){
    car_t car = car_new(700);
    assert_null(car);
}

static void posts_checkViolator__oneCarOnOnePost__countViolatorsOne(void **state){
     core_t core = core_new();
     car_t car = car_new(210);
     posts_t posts = posts_new();
     posts_addNewPost(posts, 120);
     posts_checkViolator(posts, 0, car, core);
     assert_int_equal(car_getSpeed(car), core_getViolatorSpeed(core, 0));
     assert_int_equal(posts_getPostMaxSpeed(posts, 0), core_getPostMaxSpeed(core, 0));
     assert_string_equal(posts_getPostNumber(posts, 0), core_getPostNumber(core, 0));
     assert_string_equal(car_getNumber(car), core_getViolatorCarNumber(core, 0));
     assert_int_equal(core_getAmountViolators(core), 1);
     assert_int_equal(core_getErrorStatus(core), 0);
     car_remove(car);
     posts_remove(posts);
     core_remove(core);
}

static void posts_addNewPost__fiftyOnePost_error(void **state){
    posts_t posts = posts_new();
    for(int i = 0; i < 51; i++){
        posts_addNewPost(posts, 120);
    }
    assert_int_equal(posts_getAmountPosts(posts), 50);
    assert_int_equal(posts_getErrorCode(posts), 1);
    posts_remove(posts);
}

static void core_addNewViolator__oneHundredAndOneViolator_error(void **state){
    core_t core = core_new();
    posts_t posts = posts_new();
    posts_addNewPost(posts, 120);
    car_t car = car_new(150);
    for(int i = 0; i < 101; i++){
        core_addNewViolator(core, posts, 0, car);
    }
    assert_int_equal(core_getAmountViolators(core), 100);
    assert_int_equal(core_getErrorStatus(core), 1);
    posts_remove(posts);
    core_remove(core);
    car_remove(car);
}



int main(){
    {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(posts_new__void__ZeroCountPosts),
        cmocka_unit_test(posts_addNewPost__tenNewPosts__CountPostsTen),
        cmocka_unit_test(core_new__void__ZeroCountViolators),
        cmocka_unit_test(core_new__fiveCarsOnTwoPosts__countViolatorsThree),
        cmocka_unit_test(car_new__invalidSpeed__NULL),
        cmocka_unit_test(posts_checkViolator__oneCarOnOnePost__countViolatorsOne),
        cmocka_unit_test(posts_addNewPost__fiftyOnePost_error),
        cmocka_unit_test(core_addNewViolator__oneHundredAndOneViolator_error),
        /*cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test()*/
   };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
}


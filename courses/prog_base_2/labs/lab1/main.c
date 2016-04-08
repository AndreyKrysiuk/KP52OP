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




int main(){
    {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(posts_new__void__ZeroCountPosts),
        cmocka_unit_test(posts_addNewPost__tenNewPosts__CountPostsTen),
        cmocka_unit_test(core_new__void__ZeroCountViolators),
        /*cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test(),
        cmocka_unit_test()*/
   };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
}

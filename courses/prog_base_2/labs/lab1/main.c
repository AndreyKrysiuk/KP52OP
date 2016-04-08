#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "core.h"
#include "posts.h"
#include "car.h"


/*int main()
{
    srand(time(NULL));
    car_t car1 = car_new();
    car_t car2 = car_new();
    printf("%s  speed: %d\n", car_getNumber(car1), car_getSpeed(car1));
    printf("%s  speed: %d\n", car_getNumber(car2), car_getSpeed(car2));

    posts_t system_posts = posts_new();
    posts_addNewPost(system_posts, 120);
    posts_addNewPost(system_posts, 60);
    posts_printInfoAboutPosts(system_posts);
    core_t system_core = core_new();

    if((posts_checkViolator(system_posts, 0, car1, system_core) == 0 || posts_checkViolator(system_posts, 1, car2, system_core) == 0)){
        core_printViolatorsList(system_core);
    } else {
        printf("No violators");
    }
    car_remove(car1);
    car_remove(car2);
    posts_remove(system_posts);
    core_remove(system_core);
}*/

static void posts_new_void_ZeroCountPosts(void ** state){
    posts_t posts = posts_new();
    assert_int_equal(posts_getAmountPosts(posts), 0);
    assert_int_equal(posts_getErrorCode(posts), 0);
    posts_remove(posts);
}

static void posts_addNewPost_tenNewPosts_CountPostsTen(void ** state){
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




int main(){
    {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(posts_new_void_ZeroCountPosts),
        cmocka_unit_test(posts_addNewPost_tenNewPosts_CountPostsTen),
/*        cmocka_unit_test(),
        cmocka_unit_test(),
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

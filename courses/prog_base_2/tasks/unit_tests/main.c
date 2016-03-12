#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "module.h"

static void create_void_ZeroCount(void ** state){
    network_t new_network = network_create();
    assert_int_equal(network_getAmountPosts(new_network), 0);
    assert_int_equal(network_getErrorStatus(new_network), 4);
    network_remove(new_network);
}

static void addNewPostToEnd_oneNewPost_countOne(void ** state){
    network_t new_network = network_create();
    int amountReposts = 1500;
    const char * text = "Next test";
    network_addNewPostToEnd(new_network, amountReposts, text);
    assert_int_equal(network_getAmountPosts(new_network), 1);
    assert_int_equal(network_getErrorStatus(new_network), 4);
    network_remove(new_network);
}

static void addNewPostByIndex_threeNewPost_countThree(void ** state){
    network_t new_network = network_create();
    int rep1 = 100;
    int rep2 = 200;
    int rep3 = 300;
    const char * text1 = "test1";
    const char * text2 = "test2";
    const char * text3 = "test3";
    network_addNewPostByIndex(new_network, rep1, text1, 0);
    network_addNewPostByIndex(new_network, rep2, text2, 1);
    network_addNewPostByIndex(new_network, rep3, text3, 2);
    assert_int_equal(network_getAmountPosts(new_network), 3);
    assert_int_equal(network_getErrorStatus(new_network), 4);
    network_remove(new_network);
}

static void removePostByIndex_emptyNetwork_errorEmptyNet (void ** state){
    network_t new_network = network_create();
    network_removePostByIndex(new_network, 0);
    assert_int_equal(network_getErrorStatus(new_network), 3);
    network_remove(new_network);
}

static void removePostByIndex_threePosts_countTwo (void ** state){
    network_t new_network = network_create();
    int rep1 = 100;
    int rep2 = 200;
    int rep3 = 300;
    const char * text1 = "test1";
    const char * text2 = "test2";
    const char * text3 = "test3";
    network_addNewPostByIndex(new_network, rep1, text1, 0);
    network_addNewPostByIndex(new_network, rep2, text2, 1);
    network_addNewPostByIndex(new_network, rep3, text3, 2);
    network_removePostByIndex(new_network, 0);
    assert_int_equal(network_getAmountRepostsOfPost(new_network, 0), rep2); //перевірка на те, чи змістились пости у масиві після видалення першого поста
    assert_int_equal(network_getAmountPosts(new_network), 2);
    assert_int_equal(network_getErrorStatus(new_network), 4);
    network_remove(new_network);
}

static void addNewPostByIndex_wrongIndex_errorWrongIndex(void ** state){
    network_t new_network = network_create();
    int rep = 100;
    const char * text = "lol";
    network_addNewPostByIndex(new_network, rep, text, 9);
    assert_int_equal(network_getErrorStatus(new_network), 0);
    assert_int_equal(network_getAmountPosts(new_network), 0);
    network_remove(new_network);
}

static void addNewPostToEnd_wrongAmountReposts_errorWrongAmountPosts(void ** state){
    network_t new_network = network_create();
    int rep = -100;
    const char * text = "lol";
    network_addNewPostToEnd(new_network, rep, text);
    assert_int_equal(network_getErrorStatus(new_network), 1);
    assert_int_equal(network_getAmountPosts(new_network), 0);
    network_remove(new_network);
}

static void addNewPostByIndex_wrongLengthText_errorWrongLengthText(void ** state){
    network_t new_network = network_create();
    int rep = 100;
    const char * text = "lolololololololololololololoolololololololololololololololololololololololololololololololollololololololololololo";
    network_addNewPostByIndex(new_network, rep, text, 0);
    assert_int_equal(network_getErrorStatus(new_network), 2);
    assert_int_equal(network_getAmountPosts(new_network), 0);
    network_remove(new_network);
}

static void removePostByIndex_wrongIndex_errorWrongIndex(void ** state){
    network_t new_network = network_create();
    int rep = 100;
    const char * text = "lol";
    network_addNewPostByIndex(new_network, rep, text, 0);
    network_removePostByIndex(new_network, 7);
    assert_int_equal(network_getErrorStatus(new_network), 0);
    network_remove(new_network);
}

static void getAmountRepostsOfPost_threePosts_thirdPostRepost500(void ** state){
    network_t new_network = network_create();
    int rep1 = 100;
    int rep2 = 200;
    int rep3 = 500;
    const char * text1 = "test1";
    const char * text2 = "test2";
    const char * text3 = "test3";
    network_addNewPostByIndex(new_network, rep1, text1, 0);
    network_addNewPostByIndex(new_network, rep2, text2, 1);
    network_addNewPostByIndex(new_network, rep3, text3, 2);
    assert_int_equal(network_getAmountRepostsOfPost(new_network, 2), 500);
    assert_int_equal(network_getErrorStatus(new_network), 4);
    network_remove(new_network);
}

static void setNewTextForPost_threePostsNewText_newTextForFirstPost(void ** state){
    network_t new_network = network_create();
    int rep1 = 100;
    int rep2 = 200;
    int rep3 = 500;
    const char * text1 = "test1";
    const char * text2 = "test2";
    const char * text3 = "test3";
    network_addNewPostByIndex(new_network, rep1, text1, 0);
    network_addNewPostByIndex(new_network, rep2, text2, 1);
    network_addNewPostByIndex(new_network, rep3, text3, 2);
    const char * new_text = "dovgo pusati ci testu";
    network_setNewTextForPost(new_network, 1, new_text);
    assert_string_equal(network_getTextOfPost(new_network, 1), new_text);
    assert_int_equal(network_getErrorStatus(new_network), 4);
    network_remove(new_network);
}

static void getPostsWithRepostsMoreThanValue_count7Reposts500_newCount3(void ** state){
     network_t new_network = network_create();
     int rep1 = 100;
     int rep2 = 100;
     int rep3 = 800;
     int rep4 = 900;
     int rep5 = 1000;
     int rep6 = 300;
     int rep7 = 150;
     char * text = "lol";
     network_addNewPostToEnd(new_network, rep1, text);
     network_addNewPostToEnd(new_network, rep2, text);
     network_addNewPostToEnd(new_network, rep3, text);
     network_addNewPostToEnd(new_network, rep4, text);
     network_addNewPostToEnd(new_network, rep5, text);
     network_addNewPostToEnd(new_network, rep6, text);
     network_addNewPostToEnd(new_network, rep7, text);
     network_t result = network_getPostsWithRepostsMoreThanValue(new_network, 500);
     assert_int_equal(network_getAmountPosts(result), 3);
     assert_int_equal(network_getErrorStatus(new_network), 4);
     assert_int_equal(network_getErrorStatus(result), 4);
     network_remove(result);
     network_remove(new_network);
}

static void getPostWithMaxAmountReposts_count4Max1000_reposts1000forSecondPost(void ** state){
     network_t new_network = network_create();
     int rep1 = 100;
     int rep2 = 1000;
     int rep3 = 800;
     int rep4 = 900;
     char * text = "llllllll";
     network_addNewPostToEnd(new_network, rep1, text);
     network_addNewPostToEnd(new_network, rep2, text);
     network_addNewPostToEnd(new_network, rep3, text);
     network_addNewPostToEnd(new_network, rep4, text);
     assert_int_equal(network_getPostWithMaxAmountReposts(new_network), 1);
     assert_int_equal(network_getErrorStatus(new_network), 4);
     network_remove(new_network);
}

static void network_setNewAmountRepostsForPost_count4newValue_newValueForLastPost(void ** state){
     network_t new_network = network_create();
     int rep1 = 100;
     int rep2 = 1000;
     int rep3 = 800;
     int rep4 = 900;
     char * text = "llllllll";
     network_addNewPostToEnd(new_network, rep1, text);
     network_addNewPostToEnd(new_network, rep2, text);
     network_addNewPostToEnd(new_network, rep3, text);
     network_addNewPostToEnd(new_network, rep4, text);
     int new_rep = 9999;
     network_setNewAmountRepostsForPost(new_network, 3, new_rep);
     assert_int_equal(network_getErrorStatus(new_network), 4);
     assert_int_equal(network_getAmountRepostsOfPost(new_network, 3), new_rep);
     network_remove(new_network);
}
int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(create_void_ZeroCount),
        cmocka_unit_test(addNewPostToEnd_oneNewPost_countOne),
        cmocka_unit_test(addNewPostByIndex_threeNewPost_countThree),
        cmocka_unit_test(removePostByIndex_emptyNetwork_errorEmptyNet),
        cmocka_unit_test(removePostByIndex_threePosts_countTwo),
        cmocka_unit_test(addNewPostByIndex_wrongIndex_errorWrongIndex),
        cmocka_unit_test(addNewPostToEnd_wrongAmountReposts_errorWrongAmountPosts),
        cmocka_unit_test(addNewPostByIndex_wrongLengthText_errorWrongLengthText),
        cmocka_unit_test(removePostByIndex_wrongIndex_errorWrongIndex),
        cmocka_unit_test(getAmountRepostsOfPost_threePosts_thirdPostRepost500),
        cmocka_unit_test(setNewTextForPost_threePostsNewText_newTextForFirstPost),
        cmocka_unit_test(getPostsWithRepostsMoreThanValue_count7Reposts500_newCount3),
        cmocka_unit_test(getPostWithMaxAmountReposts_count4Max1000_reposts1000forSecondPost),
        cmocka_unit_test(network_setNewAmountRepostsForPost_count4newValue_newValueForLastPost)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

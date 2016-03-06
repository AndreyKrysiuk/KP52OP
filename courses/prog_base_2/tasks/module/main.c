#include <stdio.h>
#include <stdlib.h>

#include "module.h"
int main()
{
    network_t new_network = network_create();

    network_addNewPostToEnd(new_network, 973, "Who's this?");
    network_addNewPostToEnd(new_network, 1552, "Haven't you heard, Price? They say the war is over");
    network_addNewPostByIndex(new_network, 1245, "Prisoner 627. I'm coming for you, Makarov", 1);
    network_addNewPostByIndex(new_network, 732, "My war ends with you.", 3);
    network_addNewPostByIndex(new_network, 72, "Right, what kind of name is 'Soap', eh?", 3);

    network_printNetwork(new_network);
    puts("");
    printf("%d - amount of posts in network\n", network_getAmountPosts(new_network));
    network_removePostByIndex(new_network, 3);
    puts("\nPost number 3 has been deleted");
    network_printNetwork(new_network);
    puts("");
    network_setNewTextForPost(new_network, 1, "Prisoner 6-2-7. I'm coming for you, Makarov.");
    network_printPost(new_network, 1);
    network_setNewAmountRepostsForPost(new_network, 0, 12287);
    network_printPost(new_network, 0);
    printf("Post with max amount reposts if post number %d\n", network_getPostWithMaxAmountReposts(new_network));


    printf("\nPosts with amount reposts more 800: \n");
    network_printNetwork(network_getPostsWithRepostsMoreThanValue(new_network, 800));

    network_remove(new_network);
    return 0;

}

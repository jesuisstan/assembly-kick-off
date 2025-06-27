#include "../inc/libasm.h"
#include "../inc/libasm_bonus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_list(t_list *list) {
    while (list) {
        printf(" -> %s", (char *)list->data);
        list = list->next;
    }
    printf("\n");
}

void test_push_front(const char *desc, t_list **list, char *data) {
    printf("--- %s ---\n", desc);

    if (list == NULL) {
        printf("Calling with NULL list pointer...\n");
        ft_list_push_front(list, data);
        printf("Function returned safely.\n");
        printf("-----------------------------\n\n");
        return;
    }

    printf("Before: ");
    print_list(*list);
    ft_list_push_front(list, data);
    printf("After:  ");
    print_list(*list);
    printf("-----------------------------\n\n");
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_LIST_PUSH_FRONT\n");
    printf("====================\n\n");

    t_list *list = NULL;

    test_push_front("Push to empty list", &list, "data1");
    test_push_front("Push to existing list", &list, "data2");
    test_push_front("Push another one", &list, "data3");
    test_push_front("Push with NULL list pointer", NULL, "data4");

    // Clean up
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    return 0;
} 
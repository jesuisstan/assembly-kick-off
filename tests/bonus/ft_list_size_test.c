#include "../inc/libasm_bonus.h"
#include <stdio.h>
#include <stdlib.h>

// Helper to create a list for testing
void push(t_list **list, void *data) {
    t_list *new = malloc(sizeof(t_list));
    if (!new) return;
    new->data = data;
    new->next = *list;
    *list = new;
}

void test_size(const char *desc, t_list *list, int expected) {
    printf("--- %s ---\n", desc);
    int size = ft_list_size(list);
    printf("ft_list_size: %d | expected: %d | %s\n", size, expected, size == expected ? "OK" : "KO");
    printf("-----------------------------\n\n");
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_LIST_SIZE\n");
    printf("====================\n\n");
    t_list *list = NULL;

    test_size("Size of empty list", list, 0);

    push(&list, "data1");
    test_size("Size of list with 1 element", list, 1);

    push(&list, "data2");
    push(&list, "data3");
    test_size("Size of list with 3 elements", list, 3);
    
    // Clean up
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    return 0;
} 
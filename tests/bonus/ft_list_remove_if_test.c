#include "../inc/libasm_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(t_list **list, const char *data) {
    t_list *new = malloc(sizeof(t_list));
    if (!new) exit(1);
    new->data = strdup(data);
    new->next = *list;
    *list = new;
}

void print_list(t_list *list) {
    while (list) {
        printf(" -> %s", (char *)list->data);
        list = list->next;
    }
    printf("\n");
}

void free_data(void *data) {
    free(data);
}

int cmp_str(const char *a, const char *b) {
    return strcmp(a, b);
}

void free_list(t_list **list) {
    while (*list) {
        t_list *tmp = *list;
        *list = (*list)->next;
        free_data(tmp->data);
        free(tmp);
    }
}

void test_remove(const char *desc, const char **arr, int size, const char *to_remove) {
    printf("--- %s ---\n", desc);
    t_list *list = NULL;
    for (int i = size - 1; i >= 0; i--) push(&list, arr[i]);
    printf("Before: "); print_list(list);
    ft_list_remove_if(&list, (void *)to_remove, (int (*)())cmp_str, free_data);
    printf("After:  "); print_list(list);
    free_list(&list);
    printf("-----------------------------\n\n");
}

int main(void) {
    // 1. Удаление по совпадению
    const char *arr1[] = {"A", "B", "C", "B", "D"};
    test_remove("Remove 'B' (middle, multiple)", arr1, 5, "B");

    // 2. Удаление всех
    const char *arr2[] = {"X", "X", "X"};
    test_remove("Remove all 'X' (all elements)", arr2, 3, "X");

    // 3. Удаление несуществующего
    const char *arr3[] = {"A", "B", "C"};
    test_remove("Remove 'Z' (not found)", arr3, 3, "Z");

    // 4. Удаление из пустого
    test_remove("Remove from empty list", NULL, 0, "A");

    // 5. Удаление подряд и с головы
    const char *arr5[] = {"A", "A", "B", "A"};
    test_remove("Remove 'A' (head and consecutive)", arr5, 4, "A");

    return 0;
} 
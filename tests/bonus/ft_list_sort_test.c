#include "../inc/libasm_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Helper Functions ---
void push(t_list **list, void *data) {
    t_list *new = malloc(sizeof(t_list));
    if (!new) exit(1);
    new->data = data;
    new->next = *list;
    *list = new;
}

t_list *create_list_from_arr(char **arr, int size) {
    t_list *list = NULL;
    for (int i = size - 1; i >= 0; i--) {
        push(&list, arr[i]);
    }
    return list;
}

void print_list(t_list *list) {
    while (list) {
        printf(" -> \"%s\"", (char *)list->data);
        list = list->next;
    }
    printf("\n");
}

void free_list(t_list **list) {
    while (*list) {
        t_list *tmp = *list;
        *list = (*list)->next;
        free(tmp);
    }
}

int are_lists_equal(t_list *l1, t_list *l2) {
    while (l1 && l2) {
        if (strcmp(l1->data, l2->data) != 0) return 0;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == NULL && l2 == NULL;
}

// --- Reference C implementation of list_sort ---
int cmp_func(const char *a, const char *b) {
    return strcmp(a, b);
}

void c_list_sort(t_list **begin_list, int (*cmp)()) {
    if (!begin_list || !*begin_list) return;

    t_list *current = *begin_list;
    while (current) {
        t_list *min = current;
        t_list *next = current->next;
        while (next) {
            if (cmp(min->data, next->data) > 0) {
                min = next;
            }
            next = next->next;
        }
        void *temp = current->data;
        current->data = min->data;
        min->data = temp;
        current = current->next;
    }
}

// --- Test Runner ---
void test_sort(const char *desc, char **data, int size) {
    printf("--- %s ---\n", desc);
    
    t_list *my_list = create_list_from_arr(data, size);
    t_list *ref_list = create_list_from_arr(data, size);

    printf("Before:     ");
    print_list(my_list);

    ft_list_sort(&my_list, &cmp_func);
    c_list_sort(&ref_list, &cmp_func);

    printf("ft_list_sort: ");
    print_list(my_list);
    printf("C ref sort:   ");
    print_list(ref_list);
    
    printf("Result: %s\n", are_lists_equal(my_list, ref_list) ? "OK" : "KO");
    printf("----------------------------------------\n\n");

    free_list(&my_list);
    free_list(&ref_list);
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_LIST_SORT\n");
    printf("====================\n\n");

    test_sort("Sort empty list", NULL, 0);

    char *unsorted[] = {"Charlie", "Alpha", "Delta", "Bravo"};
    test_sort("Sort unsorted list", unsorted, 4);

    char *sorted[] = {"Alpha", "Bravo", "Charlie", "Delta"};
    test_sort("Sort already sorted list", sorted, 4);

    char *reverse[] = {"Delta", "Charlie", "Bravo", "Alpha"};
    test_sort("Sort reverse sorted list", reverse, 4);

    // Новый тест: один элемент
    char *one[] = {"Solo"};
    test_sort("Sort single element list", one, 1);

    // Новый тест: два одинаковых элемента
    char *dups[] = {"Same", "Same"};
    test_sort("Sort two identical elements", dups, 2);

    // Новый тест: чередующиеся значения
    char *zigzag[] = {"B", "A", "B", "A", "B", "A"};
    test_sort("Sort alternating values", zigzag, 6);

    return 0;
} 
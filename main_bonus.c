#include "inc/libasm.h"
#include "inc/libasm_bonus.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

// ==================== HELPER FUNCTIONS ====================
int strcmp_wrapper(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

// ==================== FT_ATOI_BASE TESTS ====================
void test_atoi_base_comprehensive(void) {
    printf("=== FT_ATOI_BASE TESTS ===\n\n");
    
    printf("Base 2: ft_atoi_base(\"101010\", \"01\") = %d (expected: 42)\n", 
           ft_atoi_base("101010", "01"));
    printf("Base 314: ft_atoi_base(\"42\", \"0123456789....\") = %d (expected: 0 for invalid)\n", 
           ft_atoi_base("42", "0123456789...."));
    printf("Base 10: ft_atoi_base(\"-42\", \"0123456789\") = %d (expected: -42)\n", 
           ft_atoi_base("-42", "0123456789"));
    printf("Base 16: ft_atoi_base(\"2A\", \"0123456789abcdef\") = %d (expected: 42)\n", 
           ft_atoi_base("2A", "0123456789abcdef"));
    printf("\n");
}

// ==================== FT_LIST_PUSH_FRONT TESTS ====================
void test_list_push_front_comprehensive(void) {
    printf("=== FT_LIST_PUSH_FRONT TESTS ===\n\n");
    
    t_list *list = NULL;
    
    printf("Testing ft_list_push_front functionality:\n");
    printf("Adding 'First'...\n");
    ft_list_push_front(&list, "First");
    printf("Adding 'Second'...\n");
    ft_list_push_front(&list, "Second");
    printf("Adding 'Third'...\n");
    ft_list_push_front(&list, "Third");
    
    printf("List size: %d\n", ft_list_size(list));
    printf("List contents (LIFO order - last in, first out): ");
    t_list *current = list;
    while (current) {
        printf(" -> %s", (char *)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Cleanup
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    printf("\n");
}

// ==================== FT_LIST_SIZE TESTS ====================
void test_list_size_comprehensive(void) {
    printf("=== FT_LIST_SIZE TESTS ===\n\n");
    
    printf("Testing ft_list_size functionality:\n");
    t_list *list = NULL;
    
    printf("Empty list size: %d\n", ft_list_size(list));
    
    // Add elements manually (in reverse order for correct display)
    t_list *new1 = malloc(sizeof(t_list));
    new1->data = "21";
    new1->next = list;
    list = new1;
    
    t_list *new2 = malloc(sizeof(t_list));
    new2->data = "42";
    new2->next = list;
    list = new2;
    
    printf("List with 2 ('21' -> '42') elements size: %d\n", ft_list_size(list));
    
    // Cleanup
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    printf("\n");
}

// ==================== FT_LIST_SORT TESTS ====================
void test_list_sort_comprehensive(void) {
    printf("=== FT_LIST_SORT TESTS ===\n\n");
    
    printf("Testing ft_list_sort functionality:\n");
    
    t_list *list = NULL;
    t_list *new1 = malloc(sizeof(t_list));
    t_list *new2 = malloc(sizeof(t_list));
    t_list *new3 = malloc(sizeof(t_list));
    
    // Adding elements manually (in reverse order for correct display)
    // 1st: "Charlie" becomes last in list
    new1->data = "Charlie";
    new1->next = list;
    list = new1;
    
    // 2nd: "Alpha" becomes second in list
    new2->data = "Alpha";
    new2->next = list;
    list = new2;
    
    // 3rd: "Bravo" becomes first in list
    new3->data = "Bravo";
    new3->next = list;
    list = new3;
    
    printf("Before sorting (Bravo -> Alpha -> Charlie): ");
    t_list *current = list;
    while (current) {
        printf(" -> %s", (char *)current->data);
        current = current->next;
    }
    printf("\n");
    
    ft_list_sort(&list, strcmp_wrapper);
    
    printf("After sorting: ");
    current = list;
    while (current) {
        printf(" -> %s", (char *)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Cleanup
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    
    printf("\n");
}

// ==================== FT_LIST_REMOVE_IF TESTS ====================
void test_list_remove_if_comprehensive(void) {
    printf("=== FT_LIST_REMOVE_IF TESTS ===\n\n");
    
    printf("Testing ft_list_remove_if functionality with ft_strcmp:\n");
    
    t_list *list = NULL;
    t_list *new1 = malloc(sizeof(t_list));
    t_list *new2 = malloc(sizeof(t_list));
    t_list *new3 = malloc(sizeof(t_list));
    
    // Adding elements manually (in reverse order for correct display)
    // 1st: "First" becomes last in list
    new1->data = "First";
    new1->next = list;
    list = new1;
    
    // 2nd: "Second" becomes second in list
    new2->data = "Second";
    new2->next = list;
    list = new2;
    
    // 3rd: "Third" becomes first in list
    new3->data = "Third";
    new3->next = list;
    list = new3;
    
    printf("Before removing 'Second' (Third -> Second -> First): ");
    t_list *current = list;
    while (current) {
        printf(" -> %s", (char *)current->data);
        current = current->next;
    }
    printf("\n");
    
    ft_list_remove_if(&list, "Second", strcmp_wrapper, NULL);
    
    printf("After removing 'Second': ");
    current = list;
    while (current) {
        printf(" -> %s", (char *)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Cleanup
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    
    printf("\n");
}

int main(void) {
    printf("libasm Library Testing (Bonus Part)\n");
    printf("================================================\n\n");
    
    test_atoi_base_comprehensive();
    test_list_push_front_comprehensive();
    test_list_size_comprehensive();
    test_list_sort_comprehensive();
    test_list_remove_if_comprehensive();
    
    printf("--------------------------------\n");
    printf("All bonus tests completed!\n");
    return 0;
} 
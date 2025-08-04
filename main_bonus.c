#include "inc/libasm.h"
#include "inc/libasm_bonus.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

int main(void) {
    printf("libasm Library Demonstration (Bonus Part)\n");
    printf("=========================================\n\n");
    
    // Test ft_atoi_base
    printf("1. Testing ft_atoi_base:\n");
    printf("   ft_atoi_base(\"101010\", \"01\") = %d\n", ft_atoi_base("101010", "01"));
    printf("   ft_atoi_base(\"-42\", \"0123456789\") = %d\n", ft_atoi_base("-42", "0123456789"));
    printf("   ft_atoi_base(\"2A\", \"0123456789abcdef\") = %d\n", ft_atoi_base("2A", "0123456789abcdef"));
    printf("\n");
    
    // Test linked list functions
    printf("2. Testing linked list functions:\n");
    t_list *list = NULL;
    
    // Test ft_list_push_front
    ft_list_push_front(&list, "Third");
    ft_list_push_front(&list, "Second");
    ft_list_push_front(&list, "First");
    
    // Test ft_list_size
    int size = ft_list_size(list);
    printf("   List size: %d\n", size);
    
    // Print list
    t_list *current = list;
    printf("   List contents: ");
    while (current) {
        printf("-> %s ", (char*)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Test ft_list_sort
    ft_list_sort(&list, strcmp);
    printf("   After sorting: ");
    current = list;
    while (current) {
        printf("-> %s ", (char*)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Test ft_list_remove_if
    ft_list_remove_if(&list, "Second", strcmp, NULL); // Don't free string literals
    printf("   After removing 'Second': ");
    current = list;
    while (current) {
        printf("-> %s ", (char*)current->data);
        current = current->next;
    }
    printf("\n\n");
    
    // Clean up
    while (list) {
        t_list *temp = list;
        list = list->next;
        free(temp);
    }
    
    printf("All bonus tests completed successfully!\n");
    return 0;
} 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# include "tatami.h"

void add_Node(int x, struct Node** pptr) {
    struct Node* first_node = malloc(sizeof(struct Node));
    first_node->data = x;
    first_node->next = *pptr;
    *pptr = first_node;
}

void add_Node_Variable(char* x, struct Node_Variable** pptr) {
    struct Node_Variable* first_node = malloc(sizeof(struct Node_Variable));
    strcpy(first_node->variable, x);
    first_node->next = *pptr;
    *pptr = first_node;    
}

struct Node_Variable* add_end_of_Node_Variable(char* x, struct Node_Variable** ptr, struct Node_Variable* endptr) {
    struct Node_Variable* last_node = malloc(sizeof(struct Node_Variable));
    strcpy(last_node->variable, x);
    //formated_char_print(last_node->variable);
    last_node->next = NULL;
    if (*ptr == NULL) {
        *ptr = last_node;
        endptr = last_node;

    } else {
        endptr->next = last_node;
        endptr = last_node;
    }
    return endptr;
}

int top_Node(struct Node** headptr) {
    int data = 0;
    struct Node* tmp_node = *headptr;
    if (tmp_node != NULL) {
        data = tmp_node->data;
        *headptr = tmp_node->next;
        free(tmp_node);
        tmp_node = tmp_node->next;
    }
    return data;
}

char* top_Node_Variable(struct Node_Variable** headptr) {
    struct Node_Variable* tmp_node = *headptr;
    char text[VARIABLE_LEN] = {};
    char* p = text;
    if (tmp_node != NULL) {
        for (int i = 0; tmp_node->variable[i] == '\0'; i++) {
            text[i] = tmp_node->variable[i];
        }
        *headptr = tmp_node->next;
        free(tmp_node);   
    }

    return p;
}

void move_end_of_Node_Variable(struct Node_Variable** ptoptr, struct Node_Variable** head_ptoptr, struct Node_Variable** end) {
    struct Node_Variable* tmp_Node = *ptoptr;
    struct Node_Variable* end_Node = *end;
    *ptoptr = tmp_Node->next;
    if (*head_ptoptr == NULL) {
        *head_ptoptr = tmp_Node;    
        *end = tmp_Node;
        tmp_Node->next = NULL;
    } else {
        end_Node->next = tmp_Node;
        *end = tmp_Node;
        tmp_Node->next = NULL;
    }
}
void move_Node_Variable(struct Node_Variable** ptoptr, struct Node_Variable** head_ptoptr) {
    struct Node_Variable* tmp_Node = *ptoptr;
    *ptoptr = tmp_Node->next;
    tmp_Node->next = *head_ptoptr;
    *head_ptoptr = tmp_Node;    
}


    

void reverse_Node_Varialbe(struct Node_Variable** ptr) {
    ;
}

void empty_Node(struct Node** headptr) {
    while (*headptr != NULL) {
        top_Node(headptr);
    }
}
void empty_Node_Variable(struct Node_Variable** ptr) {
    struct Node_Variable* tmp_Node = *ptr;
    while (*ptr != NULL) {
        *ptr = tmp_Node->next;
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }
}


void print_Node(struct Node** headptr) {
    struct Node* tmp_node = *headptr;
    while (tmp_node != NULL) {
        printf("%d ", tmp_node->data);
        tmp_node = tmp_node->next;
    }
    printf("\n");
}


void print_Node_Variable(struct Node_Variable** ptr) {
    struct Node_Variable* tmp_Node = *ptr;
    int i = 0;
    while (tmp_Node != NULL) {
        //formated_char_print(tmp_Node->variable);
        for (i = 0; tmp_Node->variable[i] != '\0'; i++) {
            printf("%c", tmp_Node->variable[i]);
        }
        printf(" ");
        tmp_Node = tmp_Node->next;
    }
}

int bracket_check(char tmpchar, struct Node** ptr) {

    if (tmpchar == '('){
        add_Node(1, ptr);
    } else if (tmpchar == '[') {
        add_Node(2, ptr);
    } else if (tmpchar == '{') {
        add_Node(3, ptr);
    } else if (tmpchar == ')') {
        if (top_Node(ptr) != 1) {
            return 1;
        }
    } else if (tmpchar == ']') {
        if (top_Node(ptr) != 2) {
            return 1;
        }
    } else if (tmpchar == '}') {
        if (top_Node(ptr) != 3) {
            return 1;
        }
    }
        
    return 0;
}

void Print_tmp(char *text) {
        for (int i = 0; i < 256; i++) {
            if (text[i] == '\n') {
                break;
            }
            putchar(text[i]);
        }
        printf("\n");
}


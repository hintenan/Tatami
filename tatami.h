#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef PROMPT
#define PROMPT "//>"
#endif

#ifndef VARIABLE_LEN
#define VARIABLE_LEN 64
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

// Basic node
struct Node {
    int data;
    struct Node* next;
};
struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
};
struct Node_Variable {
    char variable[VARIABLE_LEN];
    char dtype[20];
    char data[VARIABLE_LEN];
    struct Node_Variable* next;
    struct Dtype_Node* dtype_node;
};
struct DNode_Variable {
    char variable[VARIABLE_LEN];
    char dtype[20];
    struct Node_Int* data;
    struct Node_Char* prev;
    struct Node_Char* next;
};

struct DType_Node {
    int dtype;
    int* intptr;
    double* doubleptr;
    char* charptr;
};

// Declaration
int tatami_prompt();
// Print method
void Print_tmp(char *text); 

// Add Node
void add_Node(int data, struct Node** head_ptoptr);
void add_Node_Variable(char* x, struct Node_Variable** head_ptoptr);
struct Node_Variable* add_end_of_Node_Variable(char* x, struct Node_Variable** head_ptoptr, struct Node_Variable* end_ptr);

//Delete Node

//Top Node
int top_Node(struct Node** head_ptoptr);
char* top_Node_Variable(struct Node_Variable** head_ptoptr);

// move Node
void move_Node_Variable(struct Node_Variable** ptoptr, struct Node_Variable** head);
void move_end_of_Node_Variable(struct Node_Variable** ptoptr, struct Node_Variable** head, struct Node_Variable** end);
// Reverse Node methods
void reverse_Node_Varialbe(struct Node_Variable** head_ptoptr);

// Empty Node
void empty_Node(struct Node** head_ptoptr);
void empty_Node_Variable(struct Node_Variable** head_ptoptr);

// Print Node Methods
void print_Node(struct Node** head_ptoptr);
void print_Node_Variable(struct Node_Variable** head_ptoptr);
void print_Variable_Data(struct Node_Variable** Variable_ptoptr);

// syntax check
int close_bracket_check(char text, struct Node** head_ptoptr);

// infix, prefix and postfix
int syntax_check(struct Node_Variable** cmd_ptoptr, char* text);
void formated_char_print(char* text);
int alpha_check(int index, char* text);
void identify_punct();
void in_to_postfix(struct Node_Variable** head_ptoptr);
void evaluate_postfix(struct Node_Variable** head_ptoptr);


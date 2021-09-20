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
struct Node_Int {
    int data;
    struct Node_Int* next;
};
struct Node_Double{
    double data;
    struct Node_Double* next;
};
struct DNode_Double{
    double data;
    struct DNode_Double* prev;
    struct DNode_Double* next;
};
struct Node_Var {
    char variable[VARIABLE_LEN];
    int dtype;
    union {
        struct Node_Int* node_int;
        struct Node_Double* node_double;
        //struct Node_Var* node_var;
    }datap;
    struct Node_Var* next;
};
struct Node_Operator {
    char opera[3];
    struct Node_Operator* next;
};
struct Node_Function {
    char function[VARIABLE_LEN];
    struct Node_Function* next;
};
struct Node_Op {
    int dtype;
    int* dim;
    union {
        struct Node_Int* node_int;
        struct Node_Double* node_double;
        struct Node_Var* node_var;
        struct Node_Function* node_function;
        struct Node_Int* node_operator;
    }datap;
    struct Node_Op* next;
};


// Declaration
int tatami_prompt();

// Add Node
void add_Node(int data, struct Node** head_ptoptr);
void add_DNode(int data, struct DNode** head_ptoptr);
void add_DNode_Double(double data, struct DNode_Double** head_ptoptr);
void add_Node_Var(char* x, struct Node_Var** head_ptoptr);
void add_Var_data(int x, struct Node_Var* head_ptoptr);
struct Node_Op* add_end_of_Node_Op(int data_type, struct Node_Op** ptr, struct Node_Op* endptr);
struct Node_Op* add_data(char *text, struct Node_Op* endptr);

//Delete Node
void remove_Node_Var(struct Node_Var** ptoptr);
void remove_Node_Op(struct Node_Op** ptoptr);

//Top Node
int top_Node(struct Node** head_ptoptr);
int top_DNode(struct DNode** head_ptoptr);
double top_DNode_Double(struct DNode_Double** head_ptoptr);

// Move Node
void move_Node_Op(struct Node_Op** ptoptr, struct Node_Op** head);
void move_end_of_Node_Op(struct Node_Op** ptoptr, struct Node_Op** head, struct Node_Op** end);

// Reverse Node methods

// Empty Node
void empty_Node(struct Node** head_ptoptr);
void empty_DNode(struct DNode** head_ptoptr);
void empty_DNode_Double(struct DNode_Double** head_ptoptr);
void empty_Node_Op(struct Node_Op** head_ptoptr);
void empty_Node_Var(struct Node_Var** head_ptoptr);

// Print Node Methods
void print_Node(struct Node** head_ptoptr);
void print_DNode(struct DNode** head_ptoptr);
void print_DNode_Double(struct DNode_Double** head_ptoptr);
void print_DNode_Results(struct DNode** post_ptr);
void print_DNode_Double_Results(struct DNode_Double** post_ptr);

void print_Node_Op(struct Node_Op ** Op_ptoptr);
void print_Node_Op_dtype(struct Node_Op ** Op_ptoptr);

// Print method
void Print_tmp(char *text); 


// syntax check
int syntax_check(struct Node_Op** cmd_ptoptr, char* text);
int close_bracket_check(char text, struct Node** head_ptoptr);


// infix, prefix and postfix
int replace_variable_with_data(struct Node_Var** variable_pool_ptoptr, struct Node_Op** ptotpr);

void formated_char_print(char* text);
int alpha_check(int index, char* text);
void identify_punct();
int in_to_postfix(struct Node_Op** head_ptoptr);
void evaluate_postfix(int is_double, struct Node_Var** data_pool_ptoptr, struct Node_Op** head_ptoptr);
void evaluate_postfix_d(int is_double, struct Node_Var** data_pool_ptoptr, struct Node_Op** head_ptoptr);
int scan_dot(char* text);

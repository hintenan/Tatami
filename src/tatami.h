#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#ifndef PROMPT
#define PROMPT "//> "
#define PROMPT_X = 5
#endif

#ifndef VARIABLE_LEN
#define VARIABLE_LEN 64
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

// Basic node
struct Int_Node {
    int data;
    struct Int_Node* next;
};

struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
};

struct Comm_Node {
    int dtype;
    char text[VARIABLE_LEN];
    struct Comm_Node* next;
};

// Add Node
void add_Int_Node(int data, struct Comm_Node** head_ptoptr);
void add_DNode(int data, struct DNode** head_ptoptr);
void add_Comm_Node(int data, struct Comm_Node** head_ptoptr);
void add_Comm_Node_Text(char *text, struct Comm_Node** head_ptoptr);

/*
struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
};

struct Node_Input {
    int dtype;
    char text[VARIABLE_LEN];
    int* dim;
    struct Node_Input* next;
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
    char text[VARIABLE_LEN];
    int dtype;
    union {
        int node_int;
        double node_double;
        // void* node_func;
        struct Node_Class* class;
    }datap;
    struct Node_Var* next;
};
struct Node_Class {
    char variable[64];
    int dtype;
    union {
        void (*func_void)(struct Node_Input** input_arg);
        int (*func_int)(struct Node_Input** input_arg);
        double (*func_double)(struct Node_Input** input_arg);
        char* (*func_char)(struct Node_Input** input_arg);
    }call;
    struct Node_Class* next;

};

struct Node_Operator {
    char opera[3];
    struct Node_Operator* next;
};
struct Node_Function {
    char function[VARIABLE_LEN];
    struct Node_Function* func;
    struct Node_Function* next;
};
struct Node_Op {
    int dtype;
    int* dim;
    union {
        struct Node_Int* node_operator;
        struct Node_Var* node_var;
        struct Node_Function* node_function;
        struct Node_Int* node_int;
        struct Node_Double* node_double;
    }datap;
    struct Node_Op* next;
};


// Declaration
int tatami_prompt();

// Add Node
void add_Node(int data, struct Node** head_ptoptr);
void add_DNode(int data, struct DNode** head_ptoptr);
struct Node_Input* add_end_of_Node_Input(int data_type, struct Node_Input** ptr, struct Node_Input* endptr);
void add_DNode_Double(double data, struct DNode_Double** head_ptoptr);
void add_Node_Var(char* var_text, struct Node_Var** head_ptoptr);
void add_Node_Var_data(struct Node_Input* data_ptoptr, struct Node_Var* head_ptoptr);
void add_Node_Class(char* var_text, struct Node_Class** head_ptoptr);
//struct Node_Op* add_end_of_Node_Op(int data_type, struct Node_Op** ptr, struct Node_Op* endptr);
//struct Node_Op* change_end_of_Node_Op(int data_type, struct Node_Op** ptr, struct Node_Op* endptr);
//struct Node_Op* add_data(char *text, struct Node_Op* endptr);
//struct Node_Op* add_punct(int punct, struct Node_Op* endptr);

//Delete Node
void remove_Node_Var(struct Node_Var** ptoptr);
void remove_Node_Op(struct Node_Op** ptoptr);

//Top Node
int top_Node(struct Node** head_ptoptr);
int top_DNode(struct DNode** head_ptoptr);
double top_DNode_Double(struct DNode_Double** head_ptoptr);

// Move Node
//void move_Node_Op(struct Node_Op** ptoptr, struct Node_Op** head);
//void move_end_of_Node_Op(struct Node_Op** ptoptr, struct Node_Op** head, struct Node_Op** end);

// Reverse Node methods

// Empty Node
void empty_Node(struct Node** head_ptoptr);
void empty_DNode(struct DNode** head_ptoptr);
void empty_Node_Input(struct Node_Input** head_ptoptr);
void empty_DNode_Double(struct DNode_Double** head_ptoptr);
void empty_Node_Op(struct Node_Op** head_ptoptr);
void empty_Node_Var(struct Node_Var** head_ptoptr);

// Print Node Methods
void print_Node(struct Node** head_ptoptr);
void print_DNode(struct DNode** head_ptoptr);
void print_Node_Input(struct Node_Input ** Op_ptoptr);
void print_Node_Input_dtype(struct Node_Input ** Op_ptoptr);
void print_Node_Var(struct Node_Var ** Op_ptoptr);
void print_DNode_Double(struct DNode_Double** head_ptoptr);
void print_DNode_Results(struct DNode** post_ptr);
void print_DNode_Double_Results(struct DNode_Double** post_ptr);

//void print_Node_Op(struct Node_Op ** Op_ptoptr);
//void print_Node_Op_dtype(struct Node_Op ** Op_ptoptr);

// Print method
void Print_tmp(char *text); 


// syntax check
int syntax_analysis(struct Node_Input** cmd_ptoptr, char* cmd_text);
int close_bracket_check(char text, struct Node** head_ptoptr);


// infix, prefix and postfix
int replace_variable_with_data(struct Node_Var** variable_pool_ptoptr, struct Node_Input** ptotpr);

void formated_char_print(char* text);
int alpha_check(int index, char* text);
void identify_punct();
int in_to_postfix(struct Node_Op** head_ptoptr);
void evaluate_postfix(int is_double, struct Node_Var** data_pool_ptoptr, struct Node_Op** head_ptoptr);
void evaluate_postfix_d(int is_double, struct Node_Var** data_pool_ptoptr, struct Node_Op** head_ptoptr);
int scan_dot(char* text);


struct timespec diff(struct timespec start, struct timespec end);
int load_module(struct Node_Var** pool_ptoptr, struct Node_Input** ptoptr);
*/

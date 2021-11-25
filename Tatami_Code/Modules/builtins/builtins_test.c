// build_in
#include <stdio.h>
#include <stdlib.h>
#include "tatami.h"

int add(struct Node_Input** input_arg);
void type(struct Node_Input** input_arg);
void print_something(struct Node_Input** input_arg);
double diamond(struct Node_Input** input_arg);
void add_lots_of_class(struct Node_Var** ptoptr);


int builtins() {

    // load
    struct Node_Var* __build_in__ = NULL;
    struct Node_Var** tap = &__build_in__;
    add_lots_of_class(tap);
    __build_in__ = *tap;
    // end of load

    struct Node_Input* node_input = NULL;
    struct Node_Input** node_p = &node_input;
    struct Node_Input* end = NULL;
    

    // input argument
    end = add_end_of_Node_Input(501, node_p, end);
    strcpy(end->text, "20.1");
    //end = add_end_of_Node_Input(401, node_p, end);
    //strcpy(end->text, "15");


    

    printf("%s\n", __build_in__->datap.class->variable);

    printf("%d\n", __build_in__->datap.class->dtype);
    if (__build_in__->datap.class->dtype == 499) {
        (* __build_in__->datap.class->call.func_void)(node_p);
    }
    
    return 0;

}

void add_lots_of_class(struct Node_Var** tap) {
    
    struct Node_Var* tmp_Node = *tap;
    char text[64];
    strcpy(text, "__build_in__");
    add_Node_Var(text, tap);
    tmp_Node = *tap;
    tmp_Node->dtype = 310;

    
    struct Node_Class* class = NULL;
    struct Node_Class** classp = &class;
    
    strcpy(text, "print_somethin");
    add_Node_Class(text, classp);
    class = *classp;
    class->dtype = 499;
    class->call.func_void = &print_something;
    
    strcpy(text, "diamond");
    add_Node_Class(text, classp);
    class = *classp;
    class->dtype = 501;
    class->call.func_double = &diamond;

    strcpy(text, "add");
    add_Node_Class(text, classp);
    class = *classp;
    class->dtype = 401;
    class->call.func_int = &add;

    strcpy(text, "type");
    add_Node_Class(text, classp);
    class = *classp;
    class->dtype = 499;
    class->call.func_void = &type;

    class = *classp;
    tmp_Node->datap.class = class;
    //printf("%s\n", tmp_Node->datap.class->variable);
    //printf("%d\n", (* tmp_Node->datap.class->call.func_int)(node_p));
}

int add(struct Node_Input** input_arg) {
    
    int list[2] = {401, 401};
    struct Node_Input* p = *input_arg;
    int c = 2;
    int i = 0;
    while (p != NULL){
        p = p->next;
        i += 1;
        if (i >= c) break;
    }
    if ((i < c) || (p != NULL)) {
        printf("%d\n", i);
        printf("add() takes 2 arguments.\n");
        return 0;

    }

    p = *input_arg;
    
    int a, b;
    a = atoi(p->text);
    p = p->next;
    b = atoi(p->text);
    
    return a+b;
    
}

void print_something(struct Node_Input** input_arg) {

    printf("Show something.\n");
}

double diamond (struct Node_Input** input_arg) {
    return 1.0;
}

void type(struct Node_Input** input_arg) {
    struct Node_Input* p = *input_arg;
    char text[64];
    p = p->next;
    if (p != NULL) {
        printf("type() takes 1 argument.\n");
        
    } else {
        p = *input_arg;
        switch (p->dtype){
            case 201:
                printf("<class 'str'>\n");
                break;
            case 301:
                printf("<class 'function'>\n");
                break;
            case 310:
                printf("<class 'module'>\n");
                break;
            case 401:
                printf("<class 'int'>\n");
                break;
            case 501:
                printf("<class 'double'>\n");
                break;
            default:
                ;
                break;


        }
    }
    
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# include "tatami.h"

// Add Node
void add_Int_Node(int x, struct Int_Node** pptr) {
    struct Int_Node* first_node = malloc(sizeof(struct Int_Node));
    first_node->data = x;
    first_node->next = *pptr;
    *pptr = first_node;
}

void add_DNode(int x, struct DNode** pptr) {
    struct DNode* first_node = malloc(sizeof(struct DNode));
    first_node->data = x;
    first_node->next = *pptr;
    if (first_node->next != NULL) {
        first_node->next->prev = first_node;
    }
    *pptr = first_node;
}

void add_Comm_Node(int x, struct Comm_Node** pptr) {
    struct Comm_Node* first_node = malloc(sizeof(struct Comm_Node));
    first_node->dtype = x;
    first_node->next = *pptr;
    *pptr = first_node;
}

void add_Comm_Node_Text(char *text, struct Comm_Node** ptoptr) {
    struct Comm_Node* first_node = *ptoptr;
    strcpy(first_node->text, text);
}

/*
struct Node_Op* add_end_of_Node_Op(int data_type, struct Node_Op** ptr, struct Node_Op* endptr) {
    struct Node_Op* last_node = malloc(sizeof(struct Node_Op));
    last_node->dtype = data_type;
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

struct Node_Op* change_end_of_Node_Op(int data_type, struct Node_Op** ptr, struct Node_Op* endptr) {
    endptr->dtype = data_type;
    return endptr;

}
    

struct Node_Op* add_data(char *text, struct Node_Op* endptr) {
    
    if (endptr->dtype == 401) {
        struct Node_Int* data_node = malloc(sizeof(struct Node_Int));
        data_node->data = atoi(text);
        endptr->datap.node_int = data_node;
    } else if (endptr-> dtype == 501) {
        struct Node_Double* data_node = malloc(sizeof(struct Node_Double));
        data_node->data = atof(text);
        endptr->datap.node_double = data_node;
    } else if (endptr-> dtype == 201) {
        struct Node_Var* data_node = malloc(sizeof(struct Node_Var));
        strcpy(data_node->variable, text);
        endptr->datap.node_var= data_node;
    } else if (endptr-> dtype == 301) {
        struct Node_Function* data_node = malloc(sizeof(struct Node_Function));
        strcpy(data_node->function, text);
        endptr->datap.node_function = data_node;
    }

    return endptr;
}

struct Node_Op* add_punct(int punct, struct Node_Op* endptr) {
    struct Node_Int* data_node = malloc(sizeof(struct Node_Int));
    data_node->data = punct;
    endptr->datap.node_operator= data_node;

    return endptr;
}
*/

// Delete Node
void remove_Node_Var(struct Node_Var** ptoptr) {
    struct Node_Var* tmp_node = *ptoptr;
        if (tmp_node != NULL) {
            *ptoptr = tmp_node->next;
            free(tmp_node);   
        }
}


//Top Node
int top_Node(struct Node** headptr) {
    int data = 0;
    struct Node* tmp_node = *headptr;
    if (tmp_node != NULL) {
        data = tmp_node->data;
        *headptr = tmp_node->next;
        free(tmp_node);
    }
    return data;
}

int top_DNode(struct DNode** headptr) {
    int data = 0;
    struct DNode* tmp_node = *headptr;
    if (tmp_node != NULL) {
        data = tmp_node->data;
        *headptr = tmp_node->next;
        free(tmp_node);
    }
    tmp_node = *headptr;
    if (tmp_node != NULL) {
        tmp_node->prev = NULL;
    }
    return data;
}

double top_DNode_Double(struct DNode_Double** headptr) {
    double data = 0;
    struct DNode_Double* tmp_node = *headptr;
    if (tmp_node != NULL) {
        data = tmp_node->data;
        *headptr = tmp_node->next;
        free(tmp_node);
    }
    tmp_node = *headptr;
    if (tmp_node != NULL) {
        tmp_node->prev = NULL;
    }
    return data;
}

// Move Node
// move_Node_Op(ptoptr -> head_ptoptr)
/*
void move_Node_Op(struct Node_Op** ptoptr, struct Node_Op** head_ptoptr) {
    struct Node_Op* tmp_Node = *ptoptr;
    *ptoptr = tmp_Node->next;
    tmp_Node->next = *head_ptoptr;
    *head_ptoptr = tmp_Node;    
}

void move_end_of_Node_Op(struct Node_Op** ptoptr, struct Node_Op** head_ptoptr, struct Node_Op** end) {
    struct Node_Op* tmp_Node = *ptoptr;
    struct Node_Op* end_Node = *end;
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
*/

// Reverse Node methods

// Empty Node
void empty_Node(struct Node** headptr) {
    struct Node* tmp_Node = *headptr;
    while (*headptr != NULL) {
        *headptr = tmp_Node->next;
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }
}

void empty_DNode(struct DNode** headptr) {
    struct DNode* tmp_Node = *headptr;
    while (*headptr != NULL) {
        *headptr = tmp_Node->next;
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }
}

void empty_Node_Input(struct Node_Input** headptr) {
    struct Node_Input* tmp_Node = *headptr;
    while (*headptr != NULL) {
        *headptr = tmp_Node->next;
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }
}

void empty_DNode_Double(struct DNode_Double** headptr) {
    struct DNode_Double* tmp_Node = *headptr;
    while (*headptr != NULL) {
        *headptr = tmp_Node->next;
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }
}

void empty_Node_Op(struct Node_Op** ptr) {
    struct Node_Op* tmp_Node = *ptr;
    while (*ptr != NULL) {
        *ptr = tmp_Node->next;
        if (tmp_Node->dtype < 200) free(tmp_Node->datap.node_operator);
        else if (tmp_Node->dtype < 300) free(tmp_Node->datap.node_var);
        else if (tmp_Node->dtype < 400) free(tmp_Node->datap.node_function);
        else if (tmp_Node->dtype < 500) free(tmp_Node->datap.node_int);
        else if (tmp_Node->dtype < 600) free(tmp_Node->datap.node_double);
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }
}
void empty_Node_Var(struct Node_Var** ptr) {
    struct Node_Var* tmp_Node = *ptr;
    while (*ptr != NULL) {
        *ptr = tmp_Node->next;
        free(tmp_Node);
        tmp_Node = tmp_Node->next;
    }

}

// Print Node Methods
void print_Node(struct Node** headptr) {
    struct Node* tmp_Node = *headptr;
    while (tmp_Node != NULL) {
        printf("%d ", tmp_Node->data);
        tmp_Node = tmp_Node->next;
    }
}

void print_DNode(struct DNode** headptr) {
    struct DNode* tmp_Node = *headptr;
    while (tmp_Node != NULL) {
        printf("%d ", tmp_Node->data);
        tmp_Node = tmp_Node->next;
    }
}

void print_Node_Input(struct Node_Input** headptr) {
    struct Node_Input* tmp_Node = *headptr;
    while (tmp_Node != NULL) {
        printf("%s ", tmp_Node->text);
        tmp_Node = tmp_Node->next;
    }
}

void print_Node_Input_dtype(struct Node_Input** headptr) {
    struct Node_Input* tmp_Node = *headptr;
    while (tmp_Node != NULL) {
        printf("%d ", tmp_Node->dtype);
        tmp_Node = tmp_Node->next;
    }
}

void print_Node_Var(struct Node_Var** headptr) {
    struct Node_Var* tmp_Node = *headptr;
    while (tmp_Node != NULL) {
        if (tmp_Node->dtype > 400) {
            printf("%s = %s\n", tmp_Node->variable, tmp_Node->text);
            //printf("%s = %d\n", tmp_Node->variable, tmp_Node->datap.node_int);
        } else {
            printf("%s\n", tmp_Node->variable);
        }
            tmp_Node = tmp_Node->next;
    }
}

void print_DNode_Double(struct DNode_Double** headptr) {
    struct DNode_Double* tmp_Node = *headptr;
    while (tmp_Node != NULL) {
        printf("%f ", tmp_Node->data);
        tmp_Node = tmp_Node->next;
    }
}

void print_DNode_Results(struct DNode** post_ptr) {
    struct DNode* tmp_Node = *post_ptr;
    
    int end_bracket = 0;
    if (tmp_Node->next != NULL) {
        printf("(");
        end_bracket = 1;
    }
    while(tmp_Node->next != NULL) {
        tmp_Node = tmp_Node->next;
    }
    if (tmp_Node->prev == NULL) {
        printf("%d", tmp_Node->data);
    } else {
        while(tmp_Node->prev != NULL) {
            printf("%d, ", tmp_Node->data);
            tmp_Node = tmp_Node->prev;
        }
        printf("%d", tmp_Node->data);
        tmp_Node = tmp_Node->prev;
    }
    
    if (end_bracket == 1) {
        printf(")");
    }
}

void print_DNode_Double_Results(struct DNode_Double** post_ptr) {
    struct DNode_Double* tmp_Node = *post_ptr;
    
    int end_bracket = 0;
    if (tmp_Node->next != NULL) {
        printf("(");
        end_bracket = 1;
    }
    while(tmp_Node->next != NULL) {
        tmp_Node = tmp_Node->next;
    }
    if (tmp_Node->prev == NULL) {
        printf("%f", tmp_Node->data);
    } else {
        while(tmp_Node->prev != NULL) {
            printf("%f, ", tmp_Node->data);
            tmp_Node = tmp_Node->prev;
        }
        printf("%f", tmp_Node->data);
        tmp_Node = tmp_Node->prev;
    }
    
    if (end_bracket == 1) {
        printf(")");
    }
}

/*
void print_Node_Op (struct Node_Op** ptoptr) {
    struct Node_Op* tmp_Node = *ptoptr;

    while (tmp_Node != NULL) {
        if (tmp_Node->dtype == 401) {
            printf("%d ", tmp_Node->datap.node_int->data);
        } else if (tmp_Node->dtype == 501) {
            char output[VARIABLE_LEN];
            snprintf(output, VARIABLE_LEN, "%f", tmp_Node->datap.node_double->data);
            int i = 0;
            for (i = 0; i < 10; i++) {
                if (output[i] == '\0') break;
            }
            i -= 1;
            for (; i > 0; i--) {
                if (output[i] == '0') {
                    output[i] = '\0';
                } else if (output[i] == '.') {
                    output[i + 1] = '0';
                } else {
                    break;
                }
            }
            printf("%s ", output);
            //printf("%f ", tmp_Node->datap.node_double->data);
        } else if (tmp_Node->dtype == 201) {
            printf("%s ", tmp_Node->datap.node_var->variable);
        } else if (tmp_Node->dtype == 301) {
            printf("%s ", tmp_Node->datap.node_function->function);
        } else if (tmp_Node->dtype < 100) {
            printf("%c ", tmp_Node->datap.node_operator->data);
        } else if (tmp_Node->dtype < 200) {
            printf("%c%c ", tmp_Node->datap.node_operator->data, tmp_Node->datap.node_operator->data);
        }
        tmp_Node = tmp_Node->next;
    }

}

void print_Node_Op_dtype(struct Node_Op** ptoptr) {
    struct Node_Op* tmp_Node = *ptoptr;
    while (tmp_Node != NULL) {
        printf("%d ", tmp_Node->dtype);
        tmp_Node = tmp_Node->next;
    }
}
*/

// Print method
void Print_tmp(char *text) {
        for (int i = 0; i < 256; i++) {
            if (text[i] == '\n') {
                break;
            }
            if (text[i] == '\0') {
                break;
            }
            printf("%c", text[i]);
        }
        printf("\n");
}

#include "tatami.h"
/*

int in_to_postfix(struct Node_Op** ptoptr) {
    // ptoptr: segmented dialect
    // postfix Node
    struct Node_Op* head_ptr = NULL;
    struct Node_Op** head_ptoptr = &head_ptr;
    struct Node_Op* end_ptr = NULL;
    struct Node_Op** end_ptoptr = &end_ptr;
    
    struct Node_Op* stack_ptr = NULL;
    struct Node_Op** stack_ptoptr = &stack_ptr;

    int bracket_rank = 0;
    struct Node* op_ptr = NULL;
    struct Node** op_ptoptr = &op_ptr;

    int operator_rank = 0;
    int is_assignment = 0;

    struct Node_Op* tmp_Node = *ptoptr;
    //printf("Postfix dialect: ");
    //print_Node_Op_dtype(ptoptr);
    //printf("\n");
    while (*ptoptr != NULL) {
        tmp_Node = *ptoptr;
        if ((tmp_Node->dtype == 1) || (tmp_Node->dtype == 10)) {
            move_end_of_Node_Op(ptoptr, head_ptoptr, end_ptoptr); 
        } else if (tmp_Node->dtype == 100) {
            move_end_of_Node_Op(ptoptr, head_ptoptr, end_ptoptr); 
        } else if (tmp_Node->dtype == 1002) {
            if (tmp_Node->datap.node_operator->opera[0] == '(') {
                bracket_rank += 1;
                add_Node(operator_rank, op_ptoptr);
                operator_rank = 0;
                move_Node_Op(ptoptr, stack_ptoptr);
                // handling first bracket????
            } else if (tmp_Node->datap.node_operator->opera[0] == ')') {
                bracket_rank -= 1;
                remove_Node_Op(ptoptr);
                while (stack_ptr->dtype != 1002) {
                    move_end_of_Node_Op(stack_ptoptr, head_ptoptr, end_ptoptr);
                }
                remove_Node_Op(stack_ptoptr); // remove ')'
                operator_rank = top_Node(op_ptoptr);
            }
        } else if (tmp_Node->dtype == 1000) { // operators
            if ((tmp_Node->datap.node_operator->opera[0] == '+') || (tmp_Node->datap.node_operator->opera[0] == '-')) {
                if (operator_rank == 0) {
                    move_Node_Op(ptoptr, stack_ptoptr);
                    operator_rank = 1;
                } else if (operator_rank == 1) {
                    move_end_of_Node_Op(stack_ptoptr, head_ptoptr, end_ptoptr);
                    move_Node_Op(ptoptr, stack_ptoptr);
                } else if (operator_rank == 2) {
                    while ((*stack_ptoptr != NULL) && (stack_ptr->dtype != 1002)) {
                        move_end_of_Node_Op(stack_ptoptr, head_ptoptr, end_ptoptr);
                    }
                    move_Node_Op(ptoptr, stack_ptoptr);
                    operator_rank = 1;
                }
            } else if ((tmp_Node->datap.node_operator->opera[0] == '*') || (tmp_Node->datap.node_operator->opera[0] == '/')) {
                if (operator_rank == 2) {
                    move_end_of_Node_Op(stack_ptoptr, head_ptoptr, end_ptoptr);
                    move_Node_Op(ptoptr, stack_ptoptr);
                } else {
                    move_Node_Op(ptoptr, stack_ptoptr);
                    operator_rank = 2;
                }
            }
        } else if (tmp_Node->dtype == 999) {
            move_Node_Op(ptoptr, stack_ptoptr);
            is_assignment = 1;
        } else if (tmp_Node->dtype == 1100) {
            if (is_assignment == 1) {
                printf("Can not handle complex assignment.\n");
                return 0;
                break;
            }
            // flush all
            //print_Node_Op_dtype(stack_ptoptr);
            //printf("\n");
            while ((*stack_ptoptr != NULL) && (stack_ptr->dtype != 1002)){
                //printf("flush: %d\n", stack_ptr->dtype);
                move_end_of_Node_Op(stack_ptoptr, head_ptoptr, end_ptoptr);
            }
            // add ,
            move_end_of_Node_Op(ptoptr, head_ptoptr, end_ptoptr);
            operator_rank = 0;
        }
        
    } // while

    while (*stack_ptoptr != NULL) {
        move_end_of_Node_Op(stack_ptoptr, head_ptoptr, end_ptoptr);
    }
    

    //printf("Postfix dialect: ");
    //print_Node_Op(head_ptoptr);
    //printf("\n");
    *ptoptr = *head_ptoptr;
    return 1;

}

void evaluate_postfix(int is_double, struct Node_Var** pool_ptr, struct Node_Op** ptr) {
    
    struct Node_Op* tmp_Node = *ptr;
    struct Node_Var* pool_Node = *pool_ptr;
    //if (is_double == 2) {
    //    struct DNode_Double* post = NULL;
    //    struct DNode_Double** post_ptr = &post;

    //} else {
        struct DNode* post = NULL;
        struct DNode** post_ptr = &post;
    //}
    

    struct Node_Var* assign_ptr = NULL;
    struct Node_Var** assign_ptoptr = &assign_ptr;

    int a1 = 0;
    int a2 = 0;
    int results = 0;
    
    while (tmp_Node != NULL) {
        if ((tmp_Node->dtype == 1) || (tmp_Node->dtype == 10)) {
            add_DNode(tmp_Node->datap.node_int->data, post_ptr);
        } else if (tmp_Node->dtype == 100) {
            add_Node_Var(tmp_Node->datap.node_var->variable, assign_ptoptr);
        } else if (tmp_Node->dtype == 1000) {
            if (tmp_Node->datap.node_operator->opera[0] == '+') {
                a2 = top_DNode(post_ptr);
                a1 = top_DNode(post_ptr);
                results = a1 + a2;
                add_DNode(results, post_ptr);
            } else if (tmp_Node->datap.node_operator->opera[0] == '-') {
                a2 = top_DNode(post_ptr);
                a1 = top_DNode(post_ptr);
                results = a1 - a2;
                add_DNode(results, post_ptr);
            } else if (tmp_Node->datap.node_operator->opera[0] == '*') {
                a2 = top_DNode(post_ptr);
                a1 = top_DNode(post_ptr);
                results = a1 * a2;
                add_DNode(results, post_ptr);
            } else if (tmp_Node->datap.node_operator->opera[0] == '/') {
                a2 = top_DNode(post_ptr);
                a1 = top_DNode(post_ptr);
                results = a1 / a2;
                add_DNode(results, post_ptr);
            }
        } else if (tmp_Node->dtype == 999) {
            // call add_Variable_data()
            // add or replace
            post = *post_ptr;
            while(pool_Node != NULL) {
                if (strcmp(pool_Node->variable, assign_ptr->variable) == 0) {
                    // variable found;
                    break;
                }
                pool_Node = pool_Node->next;
            }
            if (pool_Node == NULL) {
                // add
                add_Node_Var(assign_ptr->variable, pool_ptr);
                pool_Node = *pool_ptr;
                pool_Node->dtype = 1;
                add_Var_data(post->data, pool_Node);
                remove_Node_Var(assign_ptoptr);

            } else {
                // replacement
                pool_Node->dtype = 1;
                add_Var_data(post->data, pool_Node);
                remove_Node_Var(assign_ptoptr);
            }
        }
        tmp_Node = tmp_Node->next;
    }
    //print_DNode(post_ptr);
    //printf("\n");
    print_DNode_Results(post_ptr);
    printf("\n");
    empty_DNode(post_ptr);
    empty_Node_Op(ptr);
    empty_Node_Var(assign_ptoptr);
    //print_Variable_Data(data_ptr);

}

void evaluate_postfix_d(int is_double, struct Node_Var** pool_ptr, struct Node_Op** ptr) {
    
    struct Node_Op* tmp_Node = *ptr;
    struct Node_Var* pool_Node = *pool_ptr;
    
    struct DNode_Double* post = NULL;
    struct DNode_Double** post_ptr = &post;

    struct Node_Var* assign_ptr = NULL;
    struct Node_Var** assign_ptoptr = &assign_ptr;

    double a1 = 0;
    double a2 = 0;
    double results = 0;
    
    while (tmp_Node != NULL) {
        if ((tmp_Node->dtype == 1) || (tmp_Node->dtype == 10)) {
            add_DNode_Double(tmp_Node->datap.node_double->data, post_ptr);
        } else if (tmp_Node->dtype == 100) {
            add_Node_Var(tmp_Node->datap.node_var->variable, assign_ptoptr);
        } else if (tmp_Node->dtype == 1000) {
            if (tmp_Node->datap.node_operator->opera[0] == '+') {
                a2 = top_DNode_Double(post_ptr);
                a1 = top_DNode_Double(post_ptr);
                results = a1 + a2;
                add_DNode_Double(results, post_ptr);
            } else if (tmp_Node->datap.node_operator->opera[0] == '-') {
                a2 = top_DNode_Double(post_ptr);
                a1 = top_DNode_Double(post_ptr);
                results = a1 - a2;
                add_DNode_Double(results, post_ptr);
            } else if (tmp_Node->datap.node_operator->opera[0] == '*') {
                a2 = top_DNode_Double(post_ptr);
                a1 = top_DNode_Double(post_ptr);
                results = a1 * a2;
                add_DNode_Double(results, post_ptr);
            } else if (tmp_Node->datap.node_operator->opera[0] == '/') {
                a2 = top_DNode_Double(post_ptr);
                a1 = top_DNode_Double(post_ptr);
                results = a1 / a2;
                add_DNode_Double(results, post_ptr);
            }
        } else if (tmp_Node->dtype == 999) {
            // call add_Variable_data()
            // add or replace
            post = *post_ptr;
            while(pool_Node != NULL) {
                if (strcmp(pool_Node->variable, assign_ptr->variable) == 0) {
                    // variable found;
                    break;
                }
                pool_Node = pool_Node->next;
            }
            if (pool_Node == NULL) {
                // add
                add_Node_Var(assign_ptr->variable, pool_ptr);
                pool_Node = *pool_ptr;
                pool_Node->dtype = 1;
                add_Var_data(post->data, pool_Node);
                remove_Node_Var(assign_ptoptr);

            } else {
                // replacement
                pool_Node->dtype = 1;
                add_Var_data(post->data, pool_Node);
                remove_Node_Var(assign_ptoptr);
            }
        }
        tmp_Node = tmp_Node->next;
    }
    //print_DNode(post_ptr);
    //printf("\n");
    print_DNode_Double_Results(post_ptr);
    printf("\n");
    empty_DNode_Double(post_ptr);
    empty_Node_Op(ptr);
    empty_Node_Var(assign_ptoptr);
    //print_Variable_Data(data_ptr);

}
*/

void formated_char_print(char* text_ptr) {

    int iter = 0;
    printf("\n|");
    for (iter = 0; iter < VARIABLE_LEN; iter++) {
        if (text_ptr[iter] == '\0') {
            printf("\'\\0\'|");
        } else {
            printf("\'%c\'|", text_ptr[iter]);
        }
    }
    printf("\n");
}

void identify_punct() {
    int num;
    for (int i = 0; i < 127; i++) {

        num = ispunct(i);
        if (num > 0) {
            printf("(%d: %c) ", i, i);
        
        }
    }
    //printf("%d, %d", '*', ('*' == 42));
    printf("\n");
}

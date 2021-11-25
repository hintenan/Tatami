#include "tatami.h"

int replace_variable_with_data(struct Node_Var** pool_ptoptr, struct Node_Input** ptoptr) {
    
    struct Node_Input* tmp_Node = *ptoptr;
    //struct Node_Op* prev_Node = NULL;

    //struct Node_Op* assign_Node = NULL;
    struct Node_Var* pool_Node = *pool_ptoptr;
    //struct Node_Var* pool_Node = *pool_ptoptr;

    int pass_print = 1;


    //void (*a)(void);
    //int negative_sign = 0;
    //int is_double = 0;
    while (tmp_Node != NULL) {
        switch(tmp_Node->dtype) {
            case 301:
            {
                if (strcmp(tmp_Node->text, "exit") == 0) return 0;
                if (strcmp(tmp_Node->text, "dir") == 0) print_Node_Var(pool_ptoptr);
                pool_Node = *pool_ptoptr;



                pass_print = 0;

            } break;
            case 201:
            {
                while (pool_Node != NULL) {
                    if (strcmp(pool_Node->variable, tmp_Node->text) == 0) {
                        // variable exist
                        strcpy(tmp_Node->text, pool_Node->text);
                        tmp_Node->dtype = pool_Node->dtype;
                        break;
                    }
                    pool_Node = pool_Node->next;
                }
                if (pool_Node == NULL) {
                    printf("Name error: name '%s' is not defined\n", tmp_Node->text);
                    tmp_Node->next = NULL;
                    pass_print = 0; 
                }
                
                
            } break;
            
            case 299:
            {
                while (pool_Node != NULL) {
                    if (strcmp(pool_Node->variable, tmp_Node->text) == 0) {
                        // variable exist
                        add_Node_Var_data(tmp_Node->next->next->next, pool_Node);
                        break;
                    }
                    pool_Node = pool_Node->next;
                }
                if (pool_Node == NULL) {
                    add_Node_Var(tmp_Node->text, pool_ptoptr);
                    add_Node_Var_data(tmp_Node->next->next->next, *pool_ptoptr);
                }
                pool_Node = *pool_ptoptr;
                pass_print = 0;     
            } break;
            
        }

        
        tmp_Node = tmp_Node->next;
    }
    


        /*
            if (strcmp(tmp_Node->datap.node_var->variable, "exit") == 0) return 0;
            //printf("This is a variable\n");
            // assignment: variable remain as a variable.
            // formula: a = x, (a) = x
            assign_Node = tmp_Node->next;
            while ((assign_Node != NULL) && (assign_Node->dtype == 1002)) {
                    assign_Node = assign_Node->next;
            }
            if (assign_Node != NULL) {
                if (assign_Node->dtype == 999) {
                    prev_Node = tmp_Node;
                    tmp_Node = tmp_Node->next;
                    continue;
                }
            }
            // end of assignment

            while (pool_Node != NULL) {
                if (strcmp(tmp_Node->datap.node_var->variable, pool_Node->variable) == 0) {
                    // replace variable with data
                    // function here
                    //printf("Varialbe found.\n");
                    if (pool_Node->dtype == 1) {
                        free(tmp_Node->datap.node_var);
                        tmp_Node->dtype = 1;
                        char a[1] = "1";
                        add_data(a, tmp_Node);
                        tmp_Node->datap.node_int->data = pool_Node->datap.node_int->data;
                    } else if (pool_Node->dtype == 10) {
                        free(tmp_Node->datap.node_var);
                        tmp_Node->dtype = 10;
                        char a[1] = "1";
                        add_data(a, tmp_Node);
                        tmp_Node->datap.node_double->data = pool_Node->datap.node_double->data;
                    }
                    break;
                }
                pool_Node = pool_Node->next;
            }
            if (pool_Node != NULL) {
                // variable found
                // reset pool_Node
                pool_Node = *pool_ptoptr;
            } else {
                // print variable is not defined.
                printf("Syntax error: name \'");
                printf("%s", tmp_Node->datap.node_var->variable);
                printf("\' is not defined.\n");
                return 1;
            }
        

        } else if (tmp_Node->dtype <= 50) {
            if (tmp_Node->dtype == 10) {
                is_double = 2;
            }
            if (negative_sign%2) {
                negative_sign = 0;
                if (tmp_Node->dtype == 1) {
                    tmp_Node->datap.node_int->data *= -1;
                } else if (tmp_Node->dtype == 10) {
                    tmp_Node->datap.node_double->data *= -1;

                }
            }
        } else if (tmp_Node->dtype == 1001) {
            negative_sign += 1;
            if (prev_Node == NULL) {
                *ptoptr = tmp_Node->next;
                free(tmp_Node);
                tmp_Node = *ptoptr;
            } else {
                prev_Node->next = tmp_Node->next;
                free(tmp_Node);
                tmp_Node = prev_Node->next;
            }
            continue;
        }
        prev_Node = tmp_Node;
        tmp_Node = tmp_Node->next;
    }
    //printf("Variable replacement: ");
    //print_Node_Op(ptoptr);
    //printf("\n");
    //printf("Variable replacement: ");
    //print_Node_Op_dtype(ptoptr);
    //printf("\n");
    if (is_double) {
        return 3;
    }

    return 2;
    */
    //print_Node_Var(pool_ptoptr);
    if (pass_print) {
        print_Node_Input(ptoptr);
        printf("\n");
    
    }
    
    return 1;
}

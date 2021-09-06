
#include "swinhoii.h"


// define syntax check method
// first read command line into simple codeable dialect
int syntax_check (int signal_code, char* comtext) {
    // char segmentation
    char variable_text[VARIABLE_LEN] = {};
    // char punct_text[1] = {};
    int index_of_variable_text = 0;
    int index_of_comtext = 0;
    // char segmentation to structure
    // struct Segment* seg_ptr = malloc(sizeof(struct Segment));
    // struct Segment** seg_ptoptr = &seg_ptr;

    // rearranged char Node
    struct Node_Variable* ptr = NULL;
    struct Node_Variable** ptoptr = &ptr;
    struct Node_Variable* end = NULL;
    int is_operant = -1;
    // -1: init
    // 0: operator
    // 1: funtion
    // 2: digital
    // 3: variable (charactors)
    int syntax_error_signal = 0;
    // bracket error: 1
    // digit + alpha error: 2
    // operator operator error: 3
    // operant operant error: 4
    // operator starting error: 5
    // operator ending error: 6

    // bracket check
    struct Node* bracket_ptr = NULL;
    struct Node** bracket_ptoptr = &bracket_ptr;
    

        // Command text segmentation
        // isescape --> isspace --> ispunct --> isdigit --> isalpha 
    for (index_of_comtext = 0; index_of_comtext < VARIABLE_LEN; index_of_comtext++) {
        // operant or operator
        if (isdigit(comtext[index_of_comtext]) > 0) {
            // define type
            if (index_of_variable_text == 0) {
                // signal 4: operant operant error
                if (is_operant >= 2) {
                    syntax_error_signal = 4;
                    break;
                } else {
                    is_operant = 2;
                }
            }

            // write
            variable_text[index_of_variable_text] = comtext[index_of_comtext];
            index_of_variable_text += 1;
        } else if (isalpha(comtext[index_of_comtext]) > 0) {
            if (index_of_variable_text == 0) {
                // signal 4: operant operant error
                if (is_operant >= 2) {
                    syntax_error_signal = 4;
                    break;
                } else {
                    is_operant = 3;
                }
            } else { // consective
                 if (is_operant == 2) {
                     // signal 2: digit + alpha error
                     syntax_error_signal = 2;
                     break;
                 }
            }

            // write
            variable_text[index_of_variable_text] = comtext[index_of_comtext];
            index_of_variable_text += 1;
        } else if (comtext[index_of_comtext] == '(') {
            // Close bracket check
            if (close_bracket_check(comtext[index_of_comtext], bracket_ptoptr)) {
                syntax_error_signal = 11;
                break;
            }


            // brack starting
            // (a)
            if (is_operant == -1) {
                variable_text[index_of_variable_text] = comtext[index_of_comtext];
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            } else if (is_operant == 0) {
                // legal: a + (a)
                variable_text[index_of_variable_text] = comtext[index_of_comtext];
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            } else if (is_operant == 2) {
                // illegal: 1 (a)
                syntax_error_signal = 7;
                break;
            } else if (is_operant == 3) {
                // is function
                // legal: a(a)
                is_operant = 1;
                
                // BOOL: is_callable
                // BLANK

                // write
                if (index_of_variable_text > 0) {
                    end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                    index_of_variable_text = 0;
                    memset(variable_text, 0, VARIABLE_LEN);
                }
                variable_text[0] = comtext[index_of_comtext];
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            }
        } else if (comtext[index_of_comtext] == ')') {
            if (close_bracket_check(comtext[index_of_comtext], bracket_ptoptr)) {
                syntax_error_signal = 11;
                break;
            }

            if (is_operant == -1) {
                // bracket starting error
                // illega: )...
                syntax_error_signal = 7;
                break;
            } else if (is_operant == 0) {
                //illegal: a + )
                // 
                syntax_error_signal = 7;
                break;
            } else if (is_operant >= 1) {
                // is function : no argument
                // is digit: (1) 
                // is alphabet: (a)
                if (index_of_variable_text > 0) {
                    end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                    index_of_variable_text = 0;
                    memset(variable_text, 0, VARIABLE_LEN);
                }
                variable_text[0] = comtext[index_of_comtext];
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            }
        } else if (ispunct(comtext[index_of_comtext]) > 0) {
            // Arithmetic
            if ((comtext[index_of_comtext] == '*') || (comtext[index_of_comtext] == '*')) {
                if (is_operant == -1) {
                    // signal 5: operator starting error
                    syntax_error_signal = 5;
                    break;
                } else if (is_operant == 0) {
                    // signal 3: operator operator error
                    syntax_error_signal = 3;
                    break;
                }
            //} else { // is positive or negative
            }

            // write previous
            if (index_of_variable_text > 0) {
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            }
            // write punct
            is_operant = 0;
            variable_text[0] = comtext[index_of_comtext];
            end = add_end_of_Node_Variable(variable_text, ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, 0, VARIABLE_LEN);
        } else if (comtext[index_of_comtext] == ' ') {
            if (index_of_variable_text > 0) {
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            }

        } else if (comtext[index_of_comtext] == '\n') {
            // operator ending error
            if (is_operant == 0) {
                syntax_error_signal = 6;
            }
            // save last
            if (index_of_variable_text) {
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, 0, VARIABLE_LEN);
            }
            break;
        } // end if isdifit / isalpha
    } //end of for
    
    // Not empty bracket
    if (bracket_ptr != NULL) {
        syntax_error_signal = 11;
        empty_Node(bracket_ptoptr);
    }

    if (syntax_error_signal) {
        Print_tmp(comtext);
        for (int j = 0; j < index_of_comtext; j++) {
            printf(" ");
        }
        printf("|\n");
        printf("Syntax error: %d, %d\n", syntax_error_signal, index_of_comtext);
        return 0;
    } else {
        printf("Command processing: ");
        print_Node_Variable(ptoptr);
        printf("\n");
    }

    in_to_postfix(ptoptr);
    evaluate_postfix(ptoptr);
    empty_Node_Variable(ptoptr);
             
    return 1;
}

// close_bracket_check
int close_bracket_check(char text, struct Node** head_ptoptr) {
    if (text == '(') {
        add_Node(1, head_ptoptr);
    } else if (text == ')') {
        if (top_Node(head_ptoptr) != 1) {
            return 1;
        }
    }

    return 0;

}

void identify_punct() {
    int num;
    for (int i = 0; i < 100; i++) {

        num = ispunct(i);
        if (num > 0) {
            printf("(%d: %c) ", num, i);
        
        }
    }
    printf("%d, %d", '*', ('*' == 42));
    printf("\n");
}

void in_to_postfix(struct Node_Variable** pptr) {
    // Known issue: Can not handle negative or positive sign

    struct Node_Variable* head_ptr = NULL;
    struct Node_Variable** head_pptr = &head_ptr;
    struct Node_Variable* end = NULL;
    
    struct Node_Variable* stack_ptr = NULL;
    struct Node_Variable** stack_pptr = &stack_ptr;

    char variable[VARIABLE_LEN] = {};
    int rank = 0;
    int old_rank = 0;
    char operator[VARIABLE_LEN] = {};
    

    while (*pptr != NULL) {
        strcpy(variable, top_Node_Variable(pptr));
        if (isdigit(variable[0]) > 0) {
            end = add_end_of_Node_Variable(variable, head_pptr, end);
        } else if (variable[0] == '(') {
            old_rank = rank;
            rank = 0;
            add_Node_Variable(variable, stack_pptr);
        } else if (variable[0] == ')') {
            while (stack_ptr->variable[0] != '(') {
                strcpy(operator, top_Node_Variable(stack_pptr));
                end = add_end_of_Node_Variable(operator, head_pptr, end);
            }
            top_Node_Variable(stack_pptr);
            rank = old_rank;


        } else {
            if ((variable[0] == '+') || (variable[0] == '-')) {
                if (rank == 0) {
                    add_Node_Variable(variable, stack_pptr);
                    rank = 1;
                } else if (rank == 1) {
                    strcpy(operator, top_Node_Variable(stack_pptr));
                    end = add_end_of_Node_Variable(operator, head_pptr, end);
                    
                    add_Node_Variable(variable, stack_pptr);
                } else if (rank == 2) {
                    while ((*stack_pptr != NULL) && (stack_ptr->variable[0] != '(')) {
                        strcpy(operator, top_Node_Variable(stack_pptr));
                        end = add_end_of_Node_Variable(operator, head_pptr, end);
                    }

                    add_Node_Variable(variable, stack_pptr);
                    rank = 1;
                }


            } else if ((variable[0] == '*') || (variable[0] == '/')) {
                add_Node_Variable(variable, stack_pptr);
                rank = 2;
            }
        }
    }
    while (*stack_pptr != NULL) {
        strcpy(operator, top_Node_Variable(stack_pptr));
        end = add_end_of_Node_Variable(operator, head_pptr, end);
    }
    
    printf("Postfix dialect: ");
    print_Node_Variable(head_pptr);
    printf("\n");
    *pptr = *head_pptr;

}

void evaluate_postfix(struct Node_Variable** ptr) {
    struct Node_Variable* tmp_Node = *ptr;
    
    struct Node* post = NULL;
    struct Node** post_ptr = &post;

//    struct Node_Variable* Node1 = NULL;
//    struct Node_Variable* Node2 = NULL;
    int a1 = 0;
    int a2 = 0;
    int results = 0;

    while (tmp_Node != NULL) {
        if (isdigit(tmp_Node->variable[0]) > 0) {
            add_Node(atoi(tmp_Node->variable), post_ptr);
            
        } else if (tmp_Node->variable[0] == '+') {
            a2 = top_Node(post_ptr);
            a1 = top_Node(post_ptr);
            results = a1 + a2;
            add_Node(results, post_ptr);
        } else if (tmp_Node->variable[0] == '-') {
            a2 = top_Node(post_ptr);
            a1 = top_Node(post_ptr);
            results = a1 - a2;
            add_Node(results, post_ptr);
        } else if (tmp_Node->variable[0] == '*') {
            a2 = top_Node(post_ptr);
            a1 = top_Node(post_ptr);
            results = a1 * a2;
            add_Node(results, post_ptr);
        } else if (tmp_Node->variable[0] == '/') {
            a2 = top_Node(post_ptr);
            a1 = top_Node(post_ptr);
            results = a1 / a2;
            add_Node(results, post_ptr);
        }
        tmp_Node = tmp_Node->next;
    }
    print_Node(post_ptr);
    empty_Node(post_ptr);

}

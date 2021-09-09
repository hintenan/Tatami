
#include "tatami.h"


// define syntax check method
// first read command line into simple codeable dialect
int syntax_check (struct Node_Variable** cmd_ptoptr, char* comtext) {

    // char segmentation
    char variable_text[VARIABLE_LEN];
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
    int assignment = 0;
    

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
        } else if (comtext[index_of_comtext] == '=') {
            // asignment
            // processing "var = x" only by now
            // int only by now
            if (is_operant == 3) {
                is_operant = 1;
                ;
            } else {
                syntax_error_signal = 12;
                break;
            }
            // write
            assignment += 1;
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            variable_text[0] = comtext[index_of_comtext];
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
            // add '('
            variable_text[0] = '(';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
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
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            } else if (is_operant == 0) {
                // legal: a + (a)
                variable_text[index_of_variable_text] = comtext[index_of_comtext];
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                variable_text[index_of_variable_text + 1] = '\0';
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
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
                    variable_text[index_of_variable_text + 1] = '\0';
                    end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                    index_of_variable_text = 0;
                    memset(variable_text, '\0', VARIABLE_LEN);
                }
                variable_text[0] = comtext[index_of_comtext];
                variable_text[1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
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
                    variable_text[index_of_variable_text + 1] = '\0';
                    end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                    index_of_variable_text = 0;
                    memset(variable_text, '\0', VARIABLE_LEN);
                }
                variable_text[0] = comtext[index_of_comtext];
                variable_text[1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
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
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            // write punct
            is_operant = 0;
            variable_text[0] = comtext[index_of_comtext];
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (comtext[index_of_comtext] == ' ') {
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }

        } else if (comtext[index_of_comtext] == '\n') {
            // operator ending error
            if (is_operant == 0) {
                syntax_error_signal = 6;
            }
            // save last
            if (index_of_variable_text) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            break;
        } // end if isdifit / isalpha
    } //end of for
    if (assignment) {
        while (assignment) {
            variable_text[0] = ')';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
            assignment -= 1;
        }
    }
    
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

    *cmd_ptoptr = *ptoptr;
    return 1;
}

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

void in_to_postfix(struct Node_Variable** ptoptr) {
    // Known issue: Can not handle negative or positive sign

    // ptoptr: segmented dialect

    // postfix Node
    struct Node_Variable* head_ptr = NULL;
    struct Node_Variable** head_ptoptr = &head_ptr;
    struct Node_Variable* end_ptr = NULL;
    struct Node_Variable** end_ptoptr = &end_ptr;
    
    struct Node_Variable* stack_ptr = NULL;
    struct Node_Variable** stack_ptoptr = &stack_ptr;

    int bracket_rank = 0;
    struct Node* op_ptr = NULL;
    struct Node** op_ptoptr = &op_ptr;

    int operator_rank = 0;

    struct Node_Variable* tmp_Node = *ptoptr;
    
    while (*ptoptr != NULL) {
        tmp_Node = *ptoptr;
        if (isdigit(tmp_Node->variable[0]) > 0) {
            move_end_of_Node_Variable(ptoptr, head_ptoptr, end_ptoptr); 
        } else if (isalpha(tmp_Node->variable[0]) > 0) {
            move_end_of_Node_Variable(ptoptr, head_ptoptr, end_ptoptr); 
        } else if (tmp_Node->variable[0] == '(') {
            bracket_rank += 1;
            add_Node(operator_rank, op_ptoptr);
            operator_rank = 0;
            move_Node_Variable(ptoptr, stack_ptoptr);
        } else if (tmp_Node->variable[0] == ')') {
            bracket_rank -= 1;
            top_Node_Variable(ptoptr);
            while (stack_ptr->variable[0] != '(') {
                move_end_of_Node_Variable(stack_ptoptr, head_ptoptr, end_ptoptr);
            }
            top_Node_Variable(stack_ptoptr);
            operator_rank = top_Node(op_ptoptr);
    struct Node_Variable* ptr = NULL;
    struct Node_Variable** ptoptr = & ptr;
        } else { // operators
            if ((tmp_Node->variable[0] == '+') || (tmp_Node->variable[0] == '-')) {
                if (operator_rank == 0) {
                    move_Node_Variable(ptoptr, stack_ptoptr);
                    operator_rank = 1;
                } else if (operator_rank == 1) {
                    move_end_of_Node_Variable(stack_ptoptr, head_ptoptr, end_ptoptr);
                    move_Node_Variable(ptoptr, stack_ptoptr);
                } else if (operator_rank == 2) {
                    while ((*stack_ptoptr != NULL) && (stack_ptr->variable[0] != '(')) {
                        move_end_of_Node_Variable(stack_ptoptr, head_ptoptr, end_ptoptr);
                    }
                    move_Node_Variable(ptoptr, stack_ptoptr);
                    operator_rank = 1;
                }
            } else if ((tmp_Node->variable[0] == '*') || (tmp_Node->variable[0] == '/')) {
                if (operator_rank == 2) {
                    move_end_of_Node_Variable(stack_ptoptr, head_ptoptr, end_ptoptr);
                    move_Node_Variable(ptoptr, stack_ptoptr);
                } else {
                    move_Node_Variable(ptoptr, stack_ptoptr);
                    operator_rank = 2;
                }

            } else if (tmp_Node->variable[0] == '=') {
                    move_Node_Variable(ptoptr, stack_ptoptr);
            }
        }
    } // while

    while (*stack_ptoptr != NULL) {
        move_end_of_Node_Variable(stack_ptoptr, head_ptoptr, end_ptoptr);
    }
    while (*stack_ptoptr != NULL) {
        printf("Op rank remaining.");
    }

    printf("Postfix dialect: ");
    print_Node_Variable(head_ptoptr);
    printf("\n");
    *ptoptr = *head_ptoptr;

}

void evaluate_postfix(struct Node_Variable** ptr) {
    struct Node_Variable* tmp_Node = *ptr;
    struct Node* post = NULL;
    struct Node** post_ptr = &post;

    int assignment = 0;
//    struct Node_Variable* Node1 = NULL;
//    struct Node_Variable* Node2 = NULL;
    int a1 = 0;
    int a2 = 0;
    int results = 0;

    while (tmp_Node != NULL) {
        if (isalpha(tmp_Node->variable[0]) > 0) {
            assignment = 1;
        } else if (isdigit(tmp_Node->variable[0]) > 0) {
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
    if (assignment == 1) {
        if (post == NULL) {
            printf("No variable memory by now.\n");
            //print_Variable_Data();
        } else {
            char data[VARIABLE_LEN];
            sprintf(data, "%d", post->data);
            tmp_Node = *ptr;
            strcpy(tmp_Node->data, data);
            for (int i = 0; i < VARIABLE_LEN; i++) {
                if (tmp_Node->variable[i] == '\0') break;
                printf("%c", tmp_Node->variable[i]);
            }
            printf(" is ");
            for (int i = 0; i < VARIABLE_LEN; i++) {
                if (tmp_Node->data[i] == '\0') break;
                printf("%c", tmp_Node->data[i]);
            }
            printf("\n");
        }
    } else {
        print_Node(post_ptr);
    }
    empty_Node(post_ptr);

}

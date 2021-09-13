
#include "tatami.h"

// define syntax check method
// first read command line into simple codeable dialect
int syntax_check (struct Node_Variable** cmd_ptoptr, char* cmd_text) {

    // char segmentation
    char variable_text[VARIABLE_LEN];
    // char punct_text[1] = {};
    int index_of_variable_text = 0;
    int index_of_cmd_text = 0;
    // char segmentation to structure

    // rearranged char Node
    struct Node_Variable* tmp_ptr = NULL;
    struct Node_Variable** tmp_ptoptr = &tmp_ptr;
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
    // function call error: 7
    //
    // assignment error: 11
    // digits before assinment: 12
    // operation before assignment: 13

    // bracket check
    struct Node* bracket_ptr = NULL;
    struct Node** bracket_ptoptr = &bracket_ptr;
    int assignment = 0;
    int word_count = 0;
    

    // Command text segmentation
    // isescape --> isspace --> ispunct --> isdigit --> isalpha 
    for (index_of_cmd_text = 0; index_of_cmd_text < VARIABLE_LEN; index_of_cmd_text++) {
        // operant or operator
        if (isdigit(cmd_text[index_of_cmd_text]) > 0) {
            // init: define type: 2
            if (index_of_variable_text == 0) {
                // for assignment debugging 
                word_count += 1;
                // signal 4: operant operant error
                if (is_operant >= 2) {
                    syntax_error_signal = 4;
                    break;
                } else {
                    is_operant = 2;
                }
            }

            // write
            variable_text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
        } else if (isalpha(cmd_text[index_of_cmd_text]) > 0) {
            // init: define type: 3
            if (index_of_variable_text == 0) {
                // for assignment debugging 
                word_count += 1;
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
            variable_text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
        } else if (cmd_text[index_of_cmd_text] == '=') {
            // asignment
            // processing "var = x" only by now
            // int only by now
            // operation before assignment and midterm assignment
            if (word_count > 1) {
                syntax_error_signal = 13;
                break;
            }
            if (is_operant == 3) {
                is_operant = 0;
            } else {
                // digital before assignment
                syntax_error_signal = 12;
                break;
            }
            // write
            word_count = 0;
            assignment += 1;
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            variable_text[0] = cmd_text[index_of_cmd_text];
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
            // add '('
            variable_text[0] = '(';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (cmd_text[index_of_cmd_text] == '(') {
            add_Node(1, bracket_ptoptr);

            if ((is_operant == -1) || (is_operant == 0)) {
                // brack starting: (a)
                // legal: a + (a)
                ;
            //} else if (is_operant == 1) {
            // function argument
            // ............
            } else if (is_operant == 2) {
                // function call error
                // illegal: 1 (a)
                // legal: a (1)
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
                    end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                    if (is_operant == 2) {
                        end->dtype = 1;
                    } else {
                        end->dtype = 0;
                    }
                        index_of_variable_text = 0;
                        memset(variable_text, '\0', VARIABLE_LEN);
                    }
                }
            // write
            variable_text[0] = '(';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            end->dtype = 7;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (cmd_text[index_of_cmd_text] == ')') {
            if (close_bracket_check(cmd_text[index_of_cmd_text], bracket_ptoptr)) {
                syntax_error_signal = 1;
                break;
            }

            if (is_operant == 0) {
                //illegal: a + )
                // 
                syntax_error_signal = 1;
                break;
            } else if (is_operant >= 1) {
                // is function : no argument
                // is digit: (1) 
                // is alphabet: (a)
                if (index_of_variable_text > 0) {
                    variable_text[index_of_variable_text + 1] = '\0';
                    end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                    if (is_operant == 2) {
                        end->dtype = 1;
                    } else {
                        end->dtype = 0;
                    }
                        index_of_variable_text = 0;
                        memset(variable_text, '\0', VARIABLE_LEN);
                    }
                }
            variable_text[0] = ')';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            end->dtype = 7;
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        //} else if (ispunct(cmd_text[index_of_cmd_text]) > 0) {
        } else if (cmd_text[index_of_cmd_text] == '.') {
            if (index_of_variable_text == 0) {
                if (is_operant == -1) {
                    // legal
                    is_operant = 2;
                } else if (is_operant == 0) {
                    // legal
                    is_operant = 2;
                } else if (is_operant == 1) {
                    // can not handle by now...
                    is_operant = 2;
                } else if (is_operant >= 2) {
                    // op op error
                    syntax_error_signal = 3;
                    break;
                }

                // write
                variable_text[index_of_variable_text] = '0';
                index_of_variable_text += 1;
            }

            // write
            variable_text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
        } else if ((cmd_text[index_of_cmd_text] == '*') || (cmd_text[index_of_cmd_text] == '/') || (cmd_text[index_of_cmd_text] == '+') || (cmd_text[index_of_cmd_text] == '-')) {
            // Arithmetic
            if ((cmd_text[index_of_cmd_text] == '*') || (cmd_text[index_of_cmd_text] == '/')) {
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
            } else if (cmd_text[index_of_cmd_text] == '+') {
                if (is_operant == -1) {
                    continue;
                } else if (is_operant == 0) {
                    continue;
                }
            } else if (cmd_text[index_of_cmd_text] == '-') {
                if (is_operant <= 0) {
                    // write punct
                    is_operant = 0;
                    variable_text[0] = cmd_text[index_of_cmd_text];
                    variable_text[1] = '\0';
                    end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                    end->dtype = 9;
                    index_of_variable_text = 0;
                    memset(variable_text, '\0', VARIABLE_LEN);
                    continue;
                }
            }


            // write previous
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                if (is_operant == 2) {
                    end->dtype = 1;
                } else {
                    end->dtype = 0;
                }
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            // write punct
            is_operant = 0;
            variable_text[0] = cmd_text[index_of_cmd_text];
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            end->dtype = 8;
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (cmd_text[index_of_cmd_text] == ' ') {
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                if (is_operant == 2) {
                    end->dtype = 1;
                } else {
                    end->dtype = 0;
                }
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }

        } else if (cmd_text[index_of_cmd_text] == '\n') {
            // operator ending error
            if (is_operant == 0) {
                syntax_error_signal = 6;
            }
            // save last
            if (index_of_variable_text) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                if (is_operant == 2) {
                    end->dtype = 1;
                } else {
                    end->dtype = 0;
                }
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            break;
        } // end if isdifit / isalpha
    } //end of for
    while (assignment) {
        variable_text[0] = ')';
        variable_text[1] = '\0';
        end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
        memset(variable_text, '\0', VARIABLE_LEN);
        assignment -= 1;
    }
    
    // Not empty bracket
    if (bracket_ptr != NULL) {
        syntax_error_signal = 1;
    }

    if (syntax_error_signal) {
        Print_tmp(cmd_text);
        for (int j = 0; j < index_of_cmd_text; j++) {
            printf(" ");
        }
        printf("|\n");
        printf("Syntax error: %d, %d\n", syntax_error_signal, index_of_cmd_text);
        return 0;
    } else {
        printf("Command processing: ");
        print_Node_Variable(tmp_ptoptr);
        printf("\n");
    }

    *cmd_ptoptr = *tmp_ptoptr;
    empty_Node(bracket_ptoptr);

    return 1;
} // end of syntax_check





// define syntax check method
// first read command line into simple codeable dialect
int syntax_check_new (struct Node_Op** cmd_ptoptr, char* cmd_text) {


    // char segmentation
    char variable_text[VARIABLE_LEN];
    // char punct_text[1] = {};
    int index_of_variable_text = 0;
    int index_of_cmd_text = 0;
    // char segmentation to structure

    // rearranged char Node
    struct Node_Op* tmp_ptr = NULL;
    struct Node_Op** tmp_ptoptr = &tmp_ptr;
    struct Node_Op* end = NULL;
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
    // function call error: 7
    //
    // assignment error: 11
    // digits before assinment: 12
    // operation before assignment: 13

    // bracket check
    struct Node* bracket_ptr = NULL;
    struct Node** bracket_ptoptr = &bracket_ptr;
    int assignment = 0;
    int word_count = 0;
    int data_type = 0;
    

    // Command text segmentation
    // isescape --> isspace --> ispunct --> isdigit --> isalpha 
    for (index_of_cmd_text = 0; index_of_cmd_text < VARIABLE_LEN; index_of_cmd_text++) {
        // operant or operator
        if (isdigit(cmd_text[index_of_cmd_text]) > 0) {
            // init: define type: 2
            if (index_of_variable_text == 0) {
                // for assignment debugging 
                word_count += 1;
                // signal 4: operant operant error
                if (is_operant >= 2) {
                    syntax_error_signal = 4;
                    break;
                } else {
                    is_operant = 2;
                }
            }

            // write
            variable_text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
        } else if (isalpha(cmd_text[index_of_cmd_text]) > 0) {
            // init: define type: 3
            if (index_of_variable_text == 0) {
                // for assignment debugging 
                word_count += 1;
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
            variable_text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
        /*
        } else if (cmd_text[index_of_cmd_text] == '=') {
            // asignment
            // processing "var = x" only by now
            // int only by now
            // operation before assignment and midterm assignment
            if (word_count > 1) {
                syntax_error_signal = 13;
                break;
            }
            if (is_operant == 3) {
                is_operant = 0;
            } else {
                // digital before assignment
                syntax_error_signal = 12;
                break;
            }
            // write
            word_count = 0;
            assignment += 1;
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            variable_text[0] = cmd_text[index_of_cmd_text];
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
            // add '('
            variable_text[0] = '(';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (cmd_text[index_of_cmd_text] == '(') {
            add_Node(1, bracket_ptoptr);

            if ((is_operant == -1) || (is_operant == 0)) {
                // brack starting: (a)
                // legal: a + (a)
                ;
            //} else if (is_operant == 1) {
            // function argument
            // ............
            } else if (is_operant == 2) {
                // function call error
                // illegal: 1 (a)
                // legal: a (1)
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
                    end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                    if (is_operant == 2) {
                        end->dtype = 1;
                    } else {
                        end->dtype = 0;
                    }
                        index_of_variable_text = 0;
                        memset(variable_text, '\0', VARIABLE_LEN);
                    }
                }
            // write
            variable_text[0] = '(';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            end->dtype = 7;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (cmd_text[index_of_cmd_text] == ')') {
            if (close_bracket_check(cmd_text[index_of_cmd_text], bracket_ptoptr)) {
                syntax_error_signal = 1;
                break;
            }

            if (is_operant == 0) {
                //illegal: a + )
                // 
                syntax_error_signal = 1;
                break;
            } else if (is_operant >= 1) {
                // is function : no argument
                // is digit: (1) 
                // is alphabet: (a)
                if (index_of_variable_text > 0) {
                    variable_text[index_of_variable_text + 1] = '\0';
                    end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
                    if (is_operant == 2) {
                        end->dtype = 1;
                    } else {
                        end->dtype = 0;
                    }
                        index_of_variable_text = 0;
                        memset(variable_text, '\0', VARIABLE_LEN);
                    }
                }
            variable_text[0] = ')';
            variable_text[1] = '\0';
            end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
            end->dtype = 7;
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        //} else if (ispunct(cmd_text[index_of_cmd_text]) > 0) {
        */
        } else if (cmd_text[index_of_cmd_text] == '.') {
            if (index_of_variable_text == 0) {
                if (is_operant == -1) {
                    // legal
                    is_operant = 2;
                } else if (is_operant == 0) {
                    // legal
                    is_operant = 2;
                } else if (is_operant == 1) {
                    // can not handle by now...
                    is_operant = 2;
                } else if (is_operant >= 2) {
                    // op op error
                    syntax_error_signal = 3;
                    break;
                }

                // write
                variable_text[index_of_variable_text] = '0';
                index_of_variable_text += 1;
            }

            // write
            variable_text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
        } else if ((cmd_text[index_of_cmd_text] == '*') || (cmd_text[index_of_cmd_text] == '/') || (cmd_text[index_of_cmd_text] == '+') || (cmd_text[index_of_cmd_text] == '-')) {
            // Arithmetic
            if ((cmd_text[index_of_cmd_text] == '*') || (cmd_text[index_of_cmd_text] == '/')) {
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
            } else if (cmd_text[index_of_cmd_text] == '+') {
                if (is_operant == -1) {
                    continue;
                } else if (is_operant == 0) {
                    continue;
                }
            } else if (cmd_text[index_of_cmd_text] == '-') {
                if (is_operant <= 0) {
                    // write punct
                    is_operant = 0;
                    variable_text[0] = cmd_text[index_of_cmd_text];
                    variable_text[1] = '\0';
                    end = add_end_of_Node_Op(1001, tmp_ptoptr, end);
                    end = add_data(variable_text, end);
                    index_of_variable_text = 0;
                    memset(variable_text, '\0', VARIABLE_LEN);
                    continue;
                }
            }

            // write previous
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                if (is_operant == 2) {
                    data_type = scan_dot(variable_text);
                } else {
                    data_type = 100;
                }
                end = add_end_of_Node_Op(data_type, tmp_ptoptr, end);
                end = add_data(variable_text, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            // write punct
            is_operant = 0;
            variable_text[0] = cmd_text[index_of_cmd_text];
            variable_text[1] = '\0';
            end = add_end_of_Node_Op(1000, tmp_ptoptr, end);
            end = add_data(variable_text, end);
            index_of_variable_text = 0;
            memset(variable_text, '\0', VARIABLE_LEN);
        } else if (cmd_text[index_of_cmd_text] == ' ') {
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                //end = add_end_of_Node_Op(variable_text, tmp_ptoptr, end);
                if (is_operant == 2) {
                    data_type = scan_dot(variable_text);
                } else {
                    data_type = 100;
                }
                end = add_end_of_Node_Op(data_type, tmp_ptoptr, end);
                end = add_data(variable_text, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }

        } else if (cmd_text[index_of_cmd_text] == '\n') {
            // operator ending error
            if (is_operant == 0) {
                syntax_error_signal = 6;
            }
            // save last
            if (index_of_variable_text > 0) {
                variable_text[index_of_variable_text + 1] = '\0';
                //end = add_end_of_Node_Op(variable_text, tmp_ptoptr, end);
                if (is_operant == 2) {
                    data_type = scan_dot(variable_text);
                } else {
                    data_type = 100;
                }
                end = add_end_of_Node_Op(data_type, tmp_ptoptr, end);
                add_data(variable_text, end);
                index_of_variable_text = 0;
                memset(variable_text, '\0', VARIABLE_LEN);
            }
            break;
        } // end if isdifit / isalpha
    } //end of for
    /*
    while (assignment) {
        variable_text[0] = ')';
        variable_text[1] = '\0';
        end = add_end_of_Node_Variable(variable_text, tmp_ptoptr, end);
        memset(variable_text, '\0', VARIABLE_LEN);
        assignment -= 1;
    }
    */ 
    // Not empty bracket
    if (bracket_ptr != NULL) {
        syntax_error_signal = 1;
    }

    if (syntax_error_signal) {
        Print_tmp(cmd_text);
        for (int j = 0; j < index_of_cmd_text; j++) {
            printf(" ");
        }
        printf("|\n");
        printf("Syntax error: %d, %d\n", syntax_error_signal, index_of_cmd_text);
        return 0;
    } else {
        printf("Command processing: ");
        print_Node_Op(tmp_ptoptr);
        printf("\n");
    }
    *cmd_ptoptr = *tmp_ptoptr;
    empty_Node(bracket_ptoptr);

    return 1;
} // end of syntax_check

int scan_dot(char* text) {
    // 1: int
    // 10: double
    for (int i = 0; i < VARIABLE_LEN; i++) {
        if (text[i] == '\0') break;
        if (text[i] == '.') {
            return 10;
        }
    }
    return 1;
}

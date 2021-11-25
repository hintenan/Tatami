
#include "tatami.h"

// define syntax check method
// first read command line into simple codeable dialect
int syntax_analysis (struct Node_Input** cmd_ptoptr, char* cmd_text) {

    // char segmentation
    char variable_text[VARIABLE_LEN];
    // char punct_text[1] = {};
    int index_of_variable_text = 0;
    int index_of_cmd_text = 0;
    // char segmentation to structure

    // rearranged char Node
    struct Node_Input* prev = NULL;
    struct Node_Input* end = NULL;
    end = add_end_of_Node_Input(-1, cmd_ptoptr, end);
    int is_operant = -1;
    int iter = 0;
    // 0: init
    // 1: operator
    // 101: digital

    // 201: double
    // 300: variable (charactors)
    // 400: funtion
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
    struct DNode* bracket_ptr = NULL;
    struct DNode** bracket_ptoptr = &bracket_ptr;
    int assignment = 0;
    int word_count = 0;
    int negative_sign = 0;
    int bracket_signal = 0;

    //int index_of_command_text = 0;
    // Command text segmentation
    // isescape --> isspace --> ispunct --> isdigit --> isalpha 
    for (index_of_cmd_text = 0; index_of_cmd_text < VARIABLE_LEN; index_of_cmd_text++) {
        
        // operant or operator
        switch (cmd_text[index_of_cmd_text]) {
            
            case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
            {// isdigit: 1234567890
                // init: define type: 2
                if (index_of_variable_text == 0) {
                    // signal 4: operant operant error
                    // or 101
                    if (is_operant > 200) {
                        syntax_error_signal = 4;
                        break;
                    }
                    is_operant = 401;

                    // for assignment debugging 
                    // delete this?????
                    word_count += 1;

                    if (negative_sign) {
                        if (negative_sign % 2) {
                            variable_text[0] = '-';
                            index_of_variable_text += 1;
                        }
                    }
                    negative_sign = 0;
                } else if (is_operant == 101) {
                    is_operant = 501;
                }

                // write
                for (iter = index_of_cmd_text; isdigit(cmd_text[iter]); iter++) {
                    end->text[index_of_variable_text] = cmd_text[iter];
                    index_of_variable_text += 1;
                }
                index_of_cmd_text = iter - 1;

                
            } break; // end of isdigit
            case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
            case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
            case 85: case 86: case 87: case 88: case 89: case 90:
            case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
            case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
            case 117: case 118: case 119: case 120: case 121: case 122:
            { // abcdefg
                // init: define type: 3
                if (index_of_variable_text == 0) {
                    // signal 4: operant operant error
                    if (is_operant > 100) {
                        syntax_error_signal = 4;
                        break;
                    }
                    is_operant = 201;
                    
                    // for assignment debugging 
                    word_count += 1;
                    
                } else if (is_operant > 400) { // digit
                    // signal 2: digit + alpha error
                    syntax_error_signal = 2;
                    break;
                }

                // write
                for (iter = index_of_cmd_text; isalpha(cmd_text[iter]) || isdigit(cmd_text[iter]); iter++) {
                    end->text[index_of_variable_text] = cmd_text[iter];
                    index_of_variable_text += 1;
                }
                index_of_cmd_text = iter - 1;
            } break;
            case 61: // =====
            {
            if (is_operant < 200) {
                // operant operant error
                syntax_error_signal = 4;
                break;
            }
            // compare
            if (cmd_text[index_of_cmd_text + 1] == '=') {
                //logic comparision
                
                // write previous
                if (index_of_variable_text > 0) {
                    end->text[index_of_variable_text + 1] = '\0';
                    end->dtype = is_operant;
                    index_of_variable_text = 0;
                    prev = end;
                    end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                }

                // write punct
                is_operant = 111;
                end->dtype = is_operant;
                end->text[0] = 61;
                end->text[1] = 61;
                end->text[2] = '\0';
                index_of_cmd_text += 1;
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            } else {
                // asignment
                // processing "var = x" only by now
                // int only by now
                // operation before assignment and midterm assignment
                if (word_count > 1) {
                    syntax_error_signal = 13;
                    break;
                }
                if (is_operant > 400) {
                    // digital before assignment
                    syntax_error_signal = 12;
                    break;
                }

                // write
                word_count = 0;
                assignment += 1;
                // write previous
                if (index_of_variable_text > 0) {
                    end->text[index_of_variable_text + 1] = '\0';
                    end->dtype = 299;
                    index_of_variable_text = 0;
                    prev = end;
                    end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                } else {
                    prev->dtype = 299;
                }

                // write punct
                is_operant = 99;
                end->dtype = is_operant;
                end->text[0] = 61;
                end->text[1] = '\0';
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                // add '('
                end->dtype = 21;
                end->text[0] = 40;
                end->text[1] = '\0';
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                // reset is_operant
                is_operant = 0;
            }
            } break;
            case 40: // (((((
            {

            if (is_operant < 200) {
                // brack starting: (a)
                // legal: a + (a)
                ;

            } else if (is_operant < 300) {
                // function argument
                // legal: a(b)
                is_operant = 301;
                // write previous
                // write previous
                if (index_of_variable_text > 0) {
                    end->text[index_of_variable_text + 1] = '\0';
                    end->dtype = is_operant;
                    index_of_variable_text = 0;
                    prev = end;
                    end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                } else {
                    prev->dtype = 301;
                }
            
            } else {
                // function call error
                // illegal: 1 (a)
                syntax_error_signal = 7;
                break;
            }
            // bracket check
            if (is_operant == 301) {    
                is_operant = 0;
                add_DNode(4, bracket_ptoptr);
                // write
                end->dtype = 31;
                end->text[0] = 40;
                end->text[1] = '\0';
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            } else {
                add_DNode(1, bracket_ptoptr);
                // write
                end->dtype = 21;
                end->text[0] = 40;
                end->text[1] = '\0';
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }
            } break;
            case 41: // )))))
            {
            
            bracket_signal = top_DNode(bracket_ptoptr);
            if (bracket_signal == 0) {
                syntax_error_signal = 1;
                break;
            }

            if ((is_operant != 0) && (is_operant < 200)) {
                //illegal: a + )
                syntax_error_signal = 1;
                break;
            } else {
                // is function: a(), a(b)
                // is digit: (1) 
                // is alphabet: (a)
                // write previous
                if (index_of_variable_text > 0) {
                    end->text[index_of_variable_text + 1] = '\0';
                    end->dtype = is_operant;
                    index_of_variable_text = 0;
                    prev = end;
                    end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                }
            }

            if (bracket_signal == 4) {
                // write
                end->dtype = 34;
                end->text[0] = 41;
                end->text[1] = '\0';
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
                is_operant = 301;
            } else {
                // write
                end->dtype = 24;
                end->text[0] = 41;
                end->text[1] = '\0';
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }
            } break;
            case 46: // .....
            {
            // handle it as a float point only
            if (index_of_variable_text == 0) {
                if (is_operant > 100) {
                    // operant operant error
                    syntax_error_signal = 4;
                    break;
                }
                is_operant = 101;
                if (negative_sign % 2) {
                    variable_text[0] = '-';
                    index_of_variable_text += 1;
                }
                negative_sign = 0;
            
            } else if (is_operant > 500) {
                // double dot error
                syntax_error_signal = 10000;
                break;
            } else if (is_operant > 400) {
                is_operant = 501;
            } else if (is_operant > 200) {
                printf("Can not handle OOP by now.\n");
                break;
            } else if (is_operant > 100) {
                // double dot error
                syntax_error_signal = 10000;
                break;
            }

            // write
            end->text[index_of_variable_text] = cmd_text[index_of_cmd_text];
            index_of_variable_text += 1;
            } break;
        // Arithmetic
        // ***** /////
        case 42: case 47:
        {
            if (is_operant == 0) {
                // signal 5: operator starting error
                syntax_error_signal = 5;
                break;
            } else if (is_operant < 200) {
                // signal 3: operator operator error
                syntax_error_signal = 3;
                break;
            }
            // write previous
            if (index_of_variable_text > 0) {
                end->text[index_of_variable_text + 1] = '\0';
                end->dtype = is_operant;
                index_of_variable_text = 0;
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }

            // write punct
            if (cmd_text[index_of_cmd_text] == 42) {
                is_operant = 1;
            } else {
                is_operant = 2;
            }
            end->dtype = is_operant;
            end->text[0] = cmd_text[index_of_cmd_text];
            end->text[1] = '\0';
            prev = end;
            end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            } break;

        //} else { // is positive or negative
        case 43: // ++++++
        {
            if (is_operant < 100) {
                is_operant = 11;
                continue;
            } else if (is_operant < 200) {
                syntax_error_signal = 3;
                break;
            }
            // write previous
            if (index_of_variable_text > 0) {
                end->text[index_of_variable_text + 1] = '\0';
                end->dtype = is_operant;
                index_of_variable_text = 0;
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }

            // write punct
            is_operant = 11;
            end->dtype = is_operant;
            end->text[0] = 43;
            end->text[1] = '\0';
            prev = end;
            end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
        } break;
        case 45: // -----
        {
            if (is_operant < 100) {
                is_operant = 13;
                negative_sign += 1;
                continue;
            }
            // write previous
            if (index_of_variable_text > 0) {
                end->text[index_of_variable_text + 1] = '\0';
                end->dtype = is_operant;
                index_of_variable_text = 0;
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }

            // write punct
            is_operant = 12;
            end->dtype = is_operant;
            end->text[0] = 45;
            end->text[1] = '\0';
            prev = end;
            end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
        } break;
        case 44: // ,,,,,
        {
        
            // operator ending error
            if (is_operant < 200) {
                syntax_error_signal = 6;
                break;
            }
            // write previous
            if (index_of_variable_text > 0) {
                end->text[index_of_variable_text + 1] = '\0';
                end->dtype = is_operant;
                index_of_variable_text = 0;
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }
            
            // write
            //printf("a comma found.\n");
            is_operant = 0;
            end->dtype = is_operant;
            end->text[0] = 44;
            end->text[1] = '\0';
            prev = end;
            end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
        } break;
        case 32: // space
        {
        
            if (is_operant == 101) {
                // operator operator error
                syntax_error_signal = 3;
                index_of_cmd_text -= 1;
                break;
            }
            // write previous
            if (index_of_variable_text > 0) {
                end->text[index_of_variable_text + 1] = '\0';
                end->dtype = is_operant;
                index_of_variable_text = 0;
                prev = end;
                end = add_end_of_Node_Input(is_operant, cmd_ptoptr, end);
            }

            if (is_operant == 201) {
                if (strcmp("import", prev->text) == 0) {
                    prev->dtype = 399;
                    is_operant = 0;
                }
            }


        } break;
        case 10: // \n\n\n\n\n\n
        {
            // operator ending error
            if (is_operant < 200) {
                syntax_error_signal = 6;
                break;
            }
            // save last
            if (index_of_variable_text > 0) {
                end->text[index_of_variable_text + 1] = '\0';
                end->dtype = is_operant;
                index_of_variable_text = 0;
            } else {
                free(end);
                end = prev;
                end->next = NULL;
            }

            break;
        } break;
        default: 
        ;
        break;
        } // end switch (cmd_text[index_of_cmd_text])
        
        if (cmd_text[index_of_cmd_text] == '\n') break;
        if (syntax_error_signal) break;
        // if no error
        
        
    } // end of switch

    while (assignment) {
        // write punct
        end = add_end_of_Node_Input(24, cmd_ptoptr, end);
        end->text[0] = 41;
        end->text[1] = '\0';
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
        //printf("Command processing: ");
        //print_Node_Input(cmd_ptoptr);
        //printf("\n");
        printf("Command processing: ");
        print_Node_Input_dtype(cmd_ptoptr);
        printf("\n");
    }
    //*cmd_ptoptr = *cmd_ptoptr;
    empty_DNode(bracket_ptoptr);

    return 1;
} // end of syntax_check



#include "tatami.h"

// define syntax check method
// first read command line into simple codeable dialect
int syntax_analysis (char* comm_text, struct Comm_Node** comm_ptoptr) {
    // char segmentation
    char variable_text[VARIABLE_LEN];
    // char punct_text[1] = {};
    int index_of_variable_text = 0;
    int index_of_comm_text = 0;
    // char segmentation to structure

    // rearranged char Node
    struct Comm_Node* comm_node = *comm_ptoptr;
    int is_operant = -1;
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
    for (index_of_comm_text = 0; comm_text[index_of_comm_text] != '\0'; index_of_comm_text++) {
        
        // operant or operator
        switch (comm_text[index_of_comm_text]) {
            case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
                {
                    // isdigit: 1234567890
                    // init: define type: 2
                    if (index_of_variable_text == 0) {
                        // signal 4: operant operant error
                        // or 101
                        if (is_operant > TA_OPERANT) {
                            syntax_error_signal = 4;
                            goto syntax_error;
                        }
                        if (is_operant == TA_NEGATIVE_SIGN) {
                            //minus sign
                            variable_text[index_of_variable_text] = '-';
                            index_of_variable_text += 1;
                        }
                        is_operant = TA_INT;
                    }

                    // write
                    variable_text[index_of_variable_text] = comm_text[index_of_comm_text];
                    index_of_variable_text += 1;
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
                        if (is_operant > TA_OPERANT) {
                            syntax_error_signal = 4;
                            goto syntax_error;
                        }
                        if (is_operant == TA_NEGATIVE_SIGN) {
                            //minus sign
                            variable_text[index_of_variable_text] = '-';
                            index_of_variable_text += 1;
                        }
                        is_operant = TA_VAR;
                    } else if (is_operant > TA_NUMBER) { // digit
                        // signal 2: digit + alpha error
                        syntax_error_signal = 2;
                        goto syntax_error;
                    }

                    // write
                    variable_text[index_of_variable_text] = comm_text[index_of_comm_text];
                    index_of_variable_text += 1;
                } break;
            case 61: // =====
                {
                    if (is_operant < 200) {
                        // operant operant error
                        syntax_error_signal = 4;
                        break;
                    }
                    // compare
                    if (comm_text[index_of_comm_text + 1] == '=') {
                        //logic comparision
                        
                        // write previous
                        if (index_of_variable_text > 0) {
                            variable_text[index_of_variable_text] = '\0';
                            add_Comm_Node(is_operant, comm_ptoptr);
                            add_Comm_Node_Text(variable_text, comm_ptoptr);
                            index_of_variable_text = 0;
                        }
                        // write punct
                        is_operant = 111;
                        add_Comm_Node(is_operant, comm_ptoptr);
                        variable_text[0] = '=';
                        variable_text[1] = '=';
                        variable_text[2] = '\0';
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        index_of_comm_text += 1;
                    } else {
                        // asignment
                        // processing "var = x" only by now
                        // int only by now
                        // operation before assignment and midterm assignment
                        if (word_count > 1) {
                            syntax_error_signal = 13;
                            goto syntax_error;
                        }
                        if (is_operant > 400) {
                            // digital before assignment
                            syntax_error_signal = 12;
                            goto syntax_error;
                        }

                        // write
                        word_count = 0;
                        assignment += 1;
                        // write previous
                        if (index_of_variable_text > 0) {
                            variable_text[index_of_variable_text] = '\0';
                            add_Comm_Node(299, comm_ptoptr);
                            add_Comm_Node_Text(variable_text, comm_ptoptr);
                            index_of_variable_text = 0;
                        }
                        // write punct
                        is_operant = 99;
                        add_Comm_Node(is_operant, comm_ptoptr);
                        variable_text[0] = '=';
                        variable_text[1] = '\0';
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        // write punct
                        // add '('
                        add_Comm_Node(21, comm_ptoptr);
                        variable_text[0] = '(';
                        variable_text[1] = '\0';
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        // reset is_operant
                        is_operant = 0;
                    }
                } break;
            case 40: // (((((
                {
                    if (is_operant > TA_OPERANT) {
                        syntax_error_signal = 3;
                        goto syntax_error;
                    }
                        // write previous
                        if (index_of_variable_text > 0) {
                            variable_text[index_of_variable_text] = '\0';
                            add_Comm_Node(is_operant, comm_ptoptr);
                            add_Comm_Node_Text(variable_text, comm_ptoptr);
                            index_of_variable_text = 0;
                        }
                        // write punct
                        add_Comm_Node(40, comm_ptoptr);
                        variable_text[0] = '(';
                        variable_text[1] = '\0';
                        add_Comm_Node_Text(variable_text, comm_ptoptr);

                } break;
            case 41: // )))))
                {
                    if (is_operant < TA_OPERANT) {
                        syntax_error_signal = 3;
                        goto syntax_error;
                    }
                        // write previous
                        if (index_of_variable_text > 0) {
                            variable_text[index_of_variable_text] = '\0';
                            add_Comm_Node(is_operant, comm_ptoptr);
                            add_Comm_Node_Text(variable_text, comm_ptoptr);
                            index_of_variable_text = 0;
                        }
                        // write punct
                        add_Comm_Node(41, comm_ptoptr);
                        variable_text[0] = ')';
                        variable_text[1] = '\0';
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                } break;
            case 46: // .....
                {
                }break;
            // Arithmetic
            case TA_MULTIPLY:
                {
                    if (is_operant < TA_OPERANT) {
                        syntax_error_signal = 3;
                        goto syntax_error;
                    }
                    // write previous
                    if (index_of_variable_text > 0) {
                        variable_text[index_of_variable_text] = '\0';
                        add_Comm_Node(is_operant, comm_ptoptr);
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        index_of_variable_text = 0;
                    }
                    // write punct
                    is_operant = TA_MULTIPLY;
                    add_Comm_Node(is_operant, comm_ptoptr);
                    variable_text[0] = TA_MULTIPLY;
                    variable_text[1] = '\0';
                    add_Comm_Node_Text(variable_text, comm_ptoptr);
                }break;
            case TA_DIVIDE:
                {
                    if (is_operant < TA_OPERANT) {
                        syntax_error_signal = 3;
                        goto syntax_error;
                    }
                    // write previous
                    if (index_of_variable_text > 0) {
                        variable_text[index_of_variable_text] = '\0';
                        add_Comm_Node(is_operant, comm_ptoptr);
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        index_of_variable_text = 0;
                    }
                    // write punct
                    is_operant = TA_DIVIDE;
                    add_Comm_Node(is_operant, comm_ptoptr);
                    variable_text[0] = TA_DIVIDE;
                    variable_text[1] = '\0';
                    add_Comm_Node_Text(variable_text, comm_ptoptr);
                }break;
            case TA_ADD: // ++++++
                {
                    if (is_operant < 200) {
                        is_operant = TA_POSITIVE_SIGN;
                    } else {
                        switch (is_operant) {
                            case TA_NEGATIVE_SIGN:
                            case TA_POSITIVE_SIGN:
                                break;
                            default:
                                {
                                    // write previous
                                    if (index_of_variable_text > 0) {
                                        variable_text[index_of_variable_text] = '\0';
                                        add_Comm_Node(is_operant, comm_ptoptr);
                                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                                        index_of_variable_text = 0;
                                    }
                                    // write punct
                                    is_operant = TA_ADD;
                                    add_Comm_Node(is_operant, comm_ptoptr);
                                    variable_text[0] = TA_ADD;
                                    variable_text[1] = '\0';
                                    add_Comm_Node_Text(variable_text, comm_ptoptr);
                                }break;
                        } // end of switch
                    } // end of if
                } break;
            case TA_SUBTRACT: // -----
                {
                    if (is_operant < 200) {
                        is_operant = TA_NEGATIVE_SIGN;
                    } else {
                        switch (is_operant) {
                            case TA_NEGATIVE_SIGN:
                                is_operant = TA_POSITIVE_SIGN;
                                break;
                            case TA_POSITIVE_SIGN:
                                is_operant = TA_NEGATIVE_SIGN;
                                break;
                            default:
                                {
                                // write previous
                                    if (index_of_variable_text > 0) {
                                        variable_text[index_of_variable_text] = '\0';
                                        add_Comm_Node(is_operant, comm_ptoptr);
                                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                                        index_of_variable_text = 0;
                                    }
                                    // write punct
                                    is_operant = TA_SUBTRACT;
                                    add_Comm_Node(is_operant, comm_ptoptr);
                                    variable_text[0] = TA_SUBTRACT;
                                    variable_text[1] = '\0';
                                    add_Comm_Node_Text(variable_text, comm_ptoptr);
                                }break;
                        } // end of switch
                    } // end of if
                }break;
            case 44: // ,,,,,
                {
                } break;
            case 32: // space
                {
                    if ((is_operant > 200) && (is_operant < 400)) {
                        // denpedent operator;
                        syntax_error_signal = 3;
                        goto syntax_error;
                    }
                    // write previous
                    if (index_of_variable_text > 0) {
                        variable_text[index_of_variable_text] = '\0';
                        add_Comm_Node(is_operant, comm_ptoptr);
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        index_of_variable_text = 0;
                    }
                } break;
            case 10: // \n\n\n\n\n\n
                {
                    // operator ending error
                    if (is_operant < TA_OPERANT) {
                        syntax_error_signal = 6;
                        goto syntax_error;
                    }
                    // write previous
                    if (index_of_variable_text > 0) {
                        variable_text[index_of_variable_text] = '\0';
                        add_Comm_Node(is_operant, comm_ptoptr);
                        add_Comm_Node_Text(variable_text, comm_ptoptr);
                        index_of_variable_text = 0;
                    }
                } break;
            default: 
                ;
                break;
        } // end switch (comm_text[index_of_comm_text])
        if (comm_text[index_of_comm_text] == '\n') break;
    } // end of for
    // syntax erro goto here
    syntax_error:
    // syntax erro goto here
        if (syntax_error_signal) {
            printf("%s", comm_text);
            for (index_of_variable_text = 0; index_of_variable_text < index_of_comm_text; index_of_variable_text++) {
                variable_text[index_of_variable_text] = ' ';
             
            }
            variable_text[index_of_comm_text] = '|';
            variable_text[index_of_comm_text + 1] = '\0';
            printf("%s\n", variable_text);
            printf("syntax error: %d.\n", syntax_error_signal);
            
        } else {

            print_Comm_Node(comm_ptoptr);
        }

    empty_Comm_Node(comm_ptoptr);


    return 1;
} // end of syntax_check


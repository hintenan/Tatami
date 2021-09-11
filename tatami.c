#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tatami.h"
// main program
// execut input code or process line by line

int main(int argc, char *argv[]) {
    //printf("Argument No.: %d\n", argc);
    if (argc == 2) {
        if (strcmp(argv[1], "--version") == 0) {
            printf("Tatami 0.0.1 alpha\n");
        }
    // Tatami Prompt
    } else if (argc == 1) {
        printf("Tatami 0.0.1 alpha\n");
        tatami_prompt();
    }

    return 0;
}


int tatami_prompt() {

    int _not_exit_function_ = 1;
    char command_text[BUFFER_SIZE] = {};
    char tmpchar[1];
    int index_of_command_text = 0;

    struct Node_Variable* cmd_ptr = NULL;
    struct Node_Variable** cmd_ptoptr = &cmd_ptr;
    
    struct Node_Variable* var_pool_ptr = NULL;
    struct Node_Variable** var_pool_ptoptr = &var_pool_ptr;

    while (_not_exit_function_) {
        // print a promtp
        printf(PROMPT);
        // read all stdin
        while (1) {
            tmpchar[0] = getchar();
            command_text[index_of_command_text] = tmpchar[0];
            index_of_command_text += 1;
            if (tmpchar[0] == '\n') {
                break;
            }
        } // end of while (1) ** read all stdin
        //dentify_punct();
        if (index_of_command_text > 1) {
            //Print_tmp(command_text);
            if (syntax_check(cmd_ptoptr, command_text)) {
                _not_exit_function_ =  replace_variable_with_data(var_pool_ptoptr, cmd_ptoptr);
                if (_not_exit_function_ == 1) {
                    in_to_postfix(cmd_ptoptr);
                    evaluate_postfix(var_pool_ptoptr, cmd_ptoptr);
                }
            }
        }
        // reser all iteration
        index_of_command_text = 0;
        memset(command_text, '\0', BUFFER_SIZE);
    } // end of while (!_exit_function_) {

    return 1;
}

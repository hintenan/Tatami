#include "tatami.h"

int tatami_prompt() {

    int _exit_function_ = 0;
    char command_text[256] = {};
    char tmpchar[1];
    int index_of_command_text = 0;

    struct Node_Variable* ptr = NULL;
    struct Node_Variable** ptoptr = & ptr;
    
    struct Node_Variable* var_ptr = NULL;
    struct Node_Variable** var_ptoptr = &var_ptr;

    // print a promtp
    while (!_exit_function_) {
        //memset(command_text,0,sizeof(command_text));
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
            if (syntax_check(ptoptr, command_text)) {
                if (replace_variable_with_data(var_ptoptr, ptoptr)) {
                    in_to_postfix(ptoptr);
                    evaluate_postfix(var_ptoptr, ptoptr);
                }
            }
        }
        // reser all iteration
        index_of_command_text = 0;
        // clear bracket check
    } // end of while (strcmp("exit", command_text) != 0) ** print a prompt

    return 1;
}

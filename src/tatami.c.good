#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "tatami.h"
// main program
// execut input code or process line by line

/* already defined by time.h
struct timespec {
  time_t tv_sec;  // seconds
  long tv_nsec; // nanoseconds
};
*/

int diff_time(struct timespec start, struct timespec end);

int main(int argc, char *argv[]) {
    
    // Parse argument
    int n;
    if (argc > 1) {
        for (n = 1; n < argc; n++) {
            switch ((int)argv[n][0]) {
                case '-':
                    if (strcmp(argv[n], "--version") == 0) {
                        printf("Tatami 0.0.1 alpha\n");
                    } else if (strcmp(argv[1], "--punct") == 0) {
                        identify_punct();
                    }
                    break;
                default:
                    ;
                    break;
            }
        }
    // Tatami Prompt
    } else {
        printf("Tatami 0.0.1 alpha\n");
        tatami_prompt();
    }

    return 0;
}

int tatami_prompt() {
    struct timespec start, end;

    char cmd_text[VARIABLE_LEN];
    int index_of_cmd_text = 0;
    int _not_exit_loop_ = 1;

    struct Node_Input* cmd_ptr = NULL;
    struct Node_Input** cmd_ptoptr = &cmd_ptr;
    
    struct Node_Var* var_pool_ptr = NULL;
    struct Node_Var** var_pool_ptoptr = &var_pool_ptr;

    while (_not_exit_loop_) {
        // Print a promtp
        printf(PROMPT);
        // Read all command text
        while (1) {
            cmd_text[index_of_cmd_text] = getchar();
            if (cmd_text[index_of_cmd_text] == 10) break;
            index_of_cmd_text += 1;
        }
        cmd_text[index_of_cmd_text + 1] = '\0';
        //printf("%s", cmd_text);
        if (index_of_cmd_text) {
            clock_gettime(CLOCK_REALTIME, &start);
            if (syntax_analysis(cmd_ptoptr, cmd_text)) {
                if (cmd_ptr->dtype == 399) {
                    load_module(var_pool_ptoptr, cmd_ptoptr);
                } else {
                    _not_exit_loop_ =  replace_variable_with_data(var_pool_ptoptr, cmd_ptoptr);
                }

                
            /*
            if (_not_exit_function_ >= 2) {
                if (in_to_postfix(cmd_ptoptr)) {
                    if (_not_exit_function_ == 2) {
                        evaluate_postfix(_not_exit_function_, var_pool_ptoptr, cmd_ptoptr);
                    } else {
                        evaluate_postfix_d(_not_exit_function_, var_pool_ptoptr, cmd_ptoptr);

                    }
                    
                }
            
            }
            
            ;
            */
            //;
            } // end of if (syntax_chack(cmd_ptoptr, cmd_text)
            // reset all parameters
            index_of_cmd_text = 0;
            empty_Node_Input(cmd_ptoptr);

            // timer
            clock_gettime(CLOCK_REALTIME, &end);
            print_diff_time(start, end);
        } // end of if (index_of_cmd_text)
    } // end of while (_not_exit_loop_)

    return 1;
}

int print_diff_time(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    printf("Time = %ld.%09ld\n", temp.tv_sec, temp.tv_nsec);
    return 1;
}



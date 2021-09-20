#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "tatami.h"
// main program
// execut input code or process line by line
//struct timespec {
//  time_t tv_sec;  /* seconds */
//  long tv_nsec; /* nanoseconds */
//};
struct timespec diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

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
    struct timespec start, end;
    double time_used;


    int _not_exit_function_ = 1;
    char command_text[BUFFER_SIZE] = {};
    char tmpchar[1];
    int index_of_command_text = 0;

    struct Node_Op* cmd_ptr = NULL;
    struct Node_Op** cmd_ptoptr = &cmd_ptr;
    
    struct Node_Var* var_pool_ptr = NULL;
    struct Node_Var** var_pool_ptoptr = &var_pool_ptr;

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
            clock_gettime(CLOCK_REALTIME, &start);
            //Print_tmp(command_text);
            if (syntax_check(cmd_ptoptr, command_text)) {
                /*
                _not_exit_function_ =  replace_variable_with_data(var_pool_ptoptr, cmd_ptoptr);
                if (_not_exit_function_ >= 2) {
                    if (in_to_postfix(cmd_ptoptr)) {
                        if (_not_exit_function_ == 2) {
                            evaluate_postfix(_not_exit_function_, var_pool_ptoptr, cmd_ptoptr);
                        } else {
                            evaluate_postfix_d(_not_exit_function_, var_pool_ptoptr, cmd_ptoptr);

                        }
                        
                    }
                
                }
                */
                ;
            }
            clock_gettime(CLOCK_REALTIME, &end);
            struct timespec temp = diff(start, end);
            time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
            printf("Time = %f\n", time_used);
        }
        // reser all iteration
        index_of_command_text = 0;
        memset(command_text, '\0', BUFFER_SIZE);
    } // end of while (!_exit_function_) {

    return 1;
}

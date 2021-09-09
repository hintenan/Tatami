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
    // tatami_prompt();
    int _exit_function_ = 0;
    char command_text[256] = {};
    char tmpchar[1];
    int index_of_command_text = 0;

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
            syntax_check(1, command_text);
        }
        // reser all iteration
        index_of_command_text = 0;
        // clear bracket check
    } // end of while (strcmp("exit", command_text) != 0) ** print a prompt
    }
    return 0;
}



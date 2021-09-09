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



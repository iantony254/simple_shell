#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

#include "shell.h"


char* custom_getline(void) {
    static char buffer[1024];
    static int position = 0;
    static int length = 0;
    int c;
    char* line;
    int line_pos;

    /*Read in more input if buffer is empty*/ 
    if (position == length) {
        length = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (length <= 0) {
            return NULL; /*EOF or error*/
        }
        position = 0;
    }

    /*Read one character at a time until newline or end of buffer*/ 
    line = (char*) malloc(1024 * sizeof(char));
    line_pos = 0;
    while (position < length) {
        c = buffer[position++];
        if (c == '\n') {
            line[line_pos] = '\0';
            return line;
        } else {
            line[line_pos++] = c;
        }
    }

    /*End of buffer reached without finding newline*/ 
    return line;
}

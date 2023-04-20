#ifndef SHELLY_H
#define SHELLY_H

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

/**
 * File: shelly.h
 * Desc: Header file containing prototypes for all functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>




void token_handler(char *input);

#endif /* SHELLY_H */
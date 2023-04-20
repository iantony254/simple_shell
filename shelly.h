#ifndef SHELLY_H
#define SHELLY_H

/**
 * File: shelly.h
 * Desc: Header file containing prototypes for all functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int tokenize(char *input, char **args);

#endif /* SHELLY_H */
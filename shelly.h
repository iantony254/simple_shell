#ifndef _SHELLY_H_
#define _SHELLY_H_

/*
 * File: shelly.h
 * Desc: Header file containing prototypes for all functions
 *       written in the simple_shell directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int tokenize(char *input, char **args);

#endif /* _SHELLY_H_ */

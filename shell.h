#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void ela_prompt(char **prompt);
int ela_line(char **buffer, size_t *buffsize);
void ela_execve(char **args);
void ela_strtok(char *buffer, char *dlm);

#endif

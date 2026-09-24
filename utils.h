#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define LINE_BUF 512

/* Remove newline final de uma string */
void chomp(char *s);

/* Trim espaços iniciais e finais (in-place) */
void trim(char *s);

/* Safe copy of token (avoid NULL) */
char *safe_token(char *tok);

#endif // UTILS_H

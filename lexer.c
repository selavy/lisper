#include "lexer.h"
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN 256

static char token[MAX_TOKEN];
static int curr;

int Lexer_Initialize() {
    memset(&(token[0]), 0, MAX_TOKEN);
    curr = 0;
    return 0;
}

void Lexer_Tokenize(char c, char **first, char **second) {
    *first = *second = 0;

    if (c == '(') {
        *first = malloc(2);
        (*first)[0] = '(';
        (*first)[1] = 0;
        curr = 0;
    }
    else if (c == ' ') {
        if (curr) {
            (*first) = malloc(curr+1);
            memcpy(*first, &(token[0]), curr);
            (*first)[curr] = 0;
            curr = 0;
        }
    }
    else if (c == '\n' || c == '\r') {
        return;
    }
    else if (c == ')') {
        if (curr) {
            (*first) = malloc(curr+1);
            memcpy((*first), &(token[0]), curr);
            (*first)[curr] = 0;
            (*second) = malloc(2);
            (*second)[0] = ')';
            (*second)[1] = 0;
            curr = 0;
        } else {
            (*first) = malloc(2);
            (*first)[0] = ')';
            (*first)[1] = 0;
       }
    }
    else {
        token[curr++] = c;
    }
}

int Lexer_Finalize() {
    curr = 0;
    return 0;
}

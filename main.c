#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#define MAX_TOKENS 256

void PrintUsage(const char *prog);

char *tokens[MAX_TOKENS];
int curr;

int main(int argc, char *argv[]) {
    FILE *file;
    char *token1, *token2;
    char c;
    int i;
    
    if (argc == 1) {
        PrintUsage(argv[0]);
        exit(0);
    }

    file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Unable to open file: '%s'\n", argv[1]);
        exit(1);
    }

    Lexer_Initialize();
    curr = 0;
    
    while (curr < MAX_TOKENS) {
        c = fgetc(file);
        if (c == EOF) {
            break;
        }
        token1 = 0;
        token2 = 0;
        Lexer_Tokenize(c, &token1, &token2);
        if (token1) {
            tokens[curr++] = token1;
            if (token2) {
                tokens[curr++] = token2;
            }
        }
        else if (token2) {
            fprintf(stderr, "LEXER ERROR on token '%s'\n", token2);
        }
    }

    printf("TOKEN LIST:\n");
    for (i = 0; i < curr; ++i) {
        printf("'%s'\n", tokens[i]);
        free(tokens[i]);
        tokens[i] = 0;
    }
    
    Lexer_Finalize();
    fclose(file);
    return 0;
}

void PrintUsage(const char *prog) {
    printf("Usage: %s [FILE]\n", prog);
}

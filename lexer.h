#ifndef LEXER__H_
#define LEXER__H_

int Lexer_Initialize();

// first and second are sink args, client must free memory if they are not null
void Lexer_Tokenize(char c, char **first, char **second);

int Lexer_Finalize();

#endif // LEXER__H_

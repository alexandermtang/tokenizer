/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
  char *delimiters;
  char *tokenStream;
  char **tokens;
};

typedef struct TokenizerT_ TokenizerT;

// processes string, replaces "\n" with '\n' and '\0'
char *preprocessString(char *str) {
  size_t length = strlen(str);
  int i;
  for (i = 0; i < length; i++) {
    if (str[i] == '\\') {
      switch (str[i+1]) {
        case 'n': str[i] = '\n'; str[i+1] = '\0';
          break;
        case 't': str[i] = '\t'; str[i+1] = '\0';
          break;
        case 'v': str[i] = '\v'; str[i+1] = '\0';
          break;
        case 'b': str[i] = '\b'; str[i+1] = '\0';
          break;
        case 'r': str[i] = '\r'; str[i+1] = '\0';
          break;
        case 'f': str[i] = '\f'; str[i+1] = '\0';
          break;
        case '\\': str[i] = '\\'; str[i+1] = '\0';
          break;
        case 'a': str[i] = '\a'; str[i+1] = '\0';
          break;
        case '"': str[i] = '\"'; str[i+1] = '\0';
          break;
      }
    }
  }
  return str;
}

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 *
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
  size_t sepLength = strlen(separators);
  size_t tsLength = strlen(ts);

  TokenizerT *tokenizer = (TokenizerT *)malloc((sepLength + tsLength) * sizeof(char));
  tokenizer->delimiters = separators;
  tokenizer->tokenStream = ts;

  char *tokenizedString = (char *)malloc(tsLength * sizeof(char));
  strcpy(tokenizedString, ts);

  char *tempDelimiters = (char *)malloc(sepLength * sizeof(char));
  strcpy(tempDelimiters, separators);

  tokenizer->tokens = (char **)malloc(tsLength * sizeof(char));

  tempDelimiters = preprocessString(tempDelimiters);
  tokenizedString = preprocessString(tokenizedString);

  int i;
  for(i = 0; i < sepLength; i++) {
    printf("Delimiter: [0x%.2x]\n", tempDelimiters[i]);
    int j;
    for(j = 0; j < tsLength; j++) {
      if (tokenizedString[j] == tempDelimiters[i]) {
        tokenizedString[j] = '\0';
      }
    }
  }

  char *ptr = tokenizedString;
  int j = 0;
  for (i = 0; i < tsLength + 1; i++) {
    while (*ptr == '\0') {
      ptr++;
      i++;
    }
    if (tokenizedString[i] == '\0') {
      (tokenizer->tokens)[j] = ptr;
      ptr+=strlen(ptr);
      j++;
    }
  }

  free(tokenizedString);

  return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
  free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
  return *tk->tokens++;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Too few => error\n");
    return -1;
  } else if (argc > 3) {
    fprintf(stderr, "Too many => error\n");
    return -1;
  }

  printf("Input: \"%s\" \"%s\"\n", argv[1], argv[2]);

  TokenizerT *tokenizer;
  tokenizer = TKCreate(argv[1], argv[2]);

  char *token;
  while ( (token = TKGetNextToken(tokenizer)) ) {
    printf("Output: %s\n", token);
  }

  printf("Delimiters: %s\n", tokenizer->delimiters);
  printf("Token Stream: %s\n", tokenizer->tokenStream);

  TKDestroy(tokenizer);
  return 0;
}

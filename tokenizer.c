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

  // TODO need to process tempDelimiters for special characters like '\n'

  while (*tempDelimiters != '\0') {
    printf("Delimiter: %c\n", *tempDelimiters);
    int i;
    for(i = 0; i < tsLength; i++) {
      if (tokenizedString[i] == *tempDelimiters) {
        tokenizedString[i] = '\0';
      }
    }
    tempDelimiters++;
  }

  char *ptr = tokenizedString;
  int j = 0;
  int i = 0;
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
  while ( (token = TKGetNextToken(tokenizer)) )
  {
    printf("Output: %s\n", token);
  }

  printf("Delimiters: %s\n", tokenizer->delimiters);
  printf("Token Stream: %s\n", tokenizer->tokenStream);

  // Used for debug purposes
  char c = '\\';
  printf("%c [0x%.2x]", c, c);

  TKDestroy(tokenizer);
  return 0;
}

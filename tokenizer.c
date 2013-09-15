/*
 * Alexander Tang + Craig Perkins
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
  char *delimiters;
  char *tokenStream;
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
  /*TODO check for edge cases*/

  TokenizerT *tokenizer;
  tokenizer->delimiters = separators;
  tokenizer->tokenStream = ts;

  return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
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
  char *token;
  char *p, *d;
  p = tk->tokenStream;
  d = tk->delimiters;

  printf(":::\n%s %s\n:::\n", p, d);

  int s = 0;

  while (*p != *d)
  {
    printf("%s\n", p);
    p++;
    s++;
  }

  printf("%d\n", s);

  token = (char *)malloc(s);

  p = p - s;
  int i;
  for (i = 0; i < s; i++)
  {
    *token = *p;
    token++;
    p++;
  }

  printf("\n\n%d %s\n\n", s, token);








  return 0;
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
    fprintf(stderr, "Need more arguments\n");
    return 0;
  }

  TokenizerT *tokenizer;
  tokenizer = TKCreate(argv[1], argv[2]);

  printf("\"%s\" \"%s\"\n", tokenizer->delimiters, tokenizer->tokenStream);

  char *token;
  while ( token = TKGetNextToken(tokenizer) )
  {
    printf("%s\n", token);
  }

  TKDestroy(tokenizer);

  return 0;
}

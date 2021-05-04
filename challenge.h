#ifndef __CHALLENGE_HEADER_FILE__
#define __CHALLENGE_HEADER_FILE__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTING_BUFFER_SIZE 32

typedef enum {
    none,
    add,
    subtract,
    multiply,
    divide
} operator_t;

typedef struct {
    size_t size;
    unsigned int len;
    char *content;
} buffer_t;

typedef struct {
    char *content;
    void *next;
    operator_t op;
} token_t;

typedef struct {
    long num;
    long den;
} number_t;

token_t *spawn_token(const char *, const token_t *, const operator_t);
token_t *destroy_token(token_t *);
void obliterate_token_chain(token_t *);
token_t *set_next(token_t *, token_t *);

buffer_t *spawn_buffer(size_t);
int push_char(buffer_t *, const int);
void del_chars(buffer_t *, const unsigned int);
void del_char(buffer_t *);
void clear_buffer(buffer_t *);
void delete_buffer(buffer_t *);

#define next_tok(x) ((x!=NULL)?((token_t*)x->next):NULL)

#define is_whitespace(x) (((x)==' ')||((x)=='\t')||((x)=='\v'))

#endif

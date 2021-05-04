#include "challenge.h"

token_t *spawn_token(const char *content, const token_t *next, const operator_t op) {
    token_t *out;
    size_t len;
    out = calloc(sizeof(token_t), 1);
    out->op = op;
    out->next = (void*)next;
    if(!content)
        return out;
    len = strlen(content)+1;
    out->content = calloc(sizeof(char), len);
    strncpy(out->content, content, len);
    return out;
}

token_t *destroy_token(token_t *tok) {
    token_t *child;
    if(!tok)
        return NULL;
    if(tok->content)
        free(tok->content);
    child = (token_t *)tok->next;
    free(tok);
    return child;
}

void obliterate_token_chain(token_t *tok) {
    while((tok=destroy_token(tok)));
}

token_t *set_next(token_t *owner, token_t *nxt) {
    if(!owner || !nxt)
        return owner;
    owner->next = (void *)nxt;
    return nxt;
}


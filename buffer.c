#include "challenge.h"

buffer_t *spawn_buffer(size_t wantedSize) {
    buffer_t *output = calloc(sizeof(buffer_t), 1);
    output->size = (wantedSize>2) ? wantedSize : 2;
    output->content = calloc(sizeof(char), output->size);
    output->content[0] = '\0';
    output->len = 0;
    return output;
}

void resize_buffer_if_needed(buffer_t *dest) {
    if(!dest || dest->len < dest->size - 2)
        return;
    dest->size += sizeof(char)*32;
    dest->content = realloc(dest->content, dest->size);
}

static int can_read_as_num(const int input, const int len) {
    char valid[15] = ".0123456789-+Ee";
    unsigned int min = (len>1) ? 0 : 1;
    unsigned int max = (len>1) ? 11 : 15;
    unsigned int idx;
    for(idx=min;idx<max;++idx)
        if(valid[idx] == input)
            return 1;
    return 0;
}

int push_char(buffer_t *dest, const int input) {
    if(!dest)
        return input;
    resize_buffer_if_needed(dest);
    if(dest->content)
        dest->content[dest->len++] = input;
    return input;
}

void delete_buffer(buffer_t *this) {
    if(!this)
        return;
    if(this->content)
        free(this->content);
    free(this);
}

void clear_buffer(buffer_t *this) {
    if(!this || !this->content || this->len<1)
        return;
    this->len = 0;
    memset(this->content, '\0', this->size);
}

void del_char(buffer_t *this) {
    if(!this || !this->content || this->len<1)
        return;
    this->len-=1;
    this->content[this->len]='\0';
}

void del_chars(buffer_t *this, const unsigned int quant) {
    unsigned int idx;
    for(idx=0;idx<quant;idx++)
        del_char(this);
}


#include "challenge.h"

number_t show(const number_t this) {
    long fractions=(this.num%this.den);
    long wholes=((this.num-fractions)/this.den);
    if(wholes>0)
        printf("%ld%s", wholes, (fractions>0)?"_":"");
    if(fractions>0)
        printf("%ld/%ld", fractions, this.den);
    putchar('\n');
    return this;
}

token_t *consume_token(buffer_t *buf) {
    token_t *out;
    if(!buf || buf->len < 1)
        return NULL;
    out = spawn_token(buf->content, NULL, none);
    clear_buffer(buf);
    return out;
}

token_t *read_stream(FILE *src, buffer_t *buf) {
    token_t *head=spawn_token(NULL, NULL, none);
    token_t *tail=head, *got;
    int input, prev = ' ';

    clear_buffer(buf);
    while((input = fgetc(src)) != EOF && input != '\n') {
        if(is_whitespace(input)) {
            tail = set_next(tail, consume_token(buf));
            prev = ' ';
            while(is_whitespace(input) && input != EOF)
                input = fgetc(src);
        }
        switch(input) {
            case '+':
                tail = set_next(tail, consume_token(buf));
                tail = set_next(tail, spawn_token(NULL, NULL, add));
                continue;
            case '*':
                tail = set_next(tail, consume_token(buf));
                tail = set_next(tail, spawn_token(NULL, NULL, multiply));
                continue;
            case '/':
                if(!isdigit(prev)) {
                    tail = set_next(tail, consume_token(buf));
                    tail = set_next(tail, spawn_token(NULL, NULL, divide));
                    continue;
                }
                break;
            case '-':
                input = fgetc(src);
                if(isdigit(input)) { /* Negative number */
                    push_char(buf, '-');
                    push_char(buf, input);
                    continue;
                }
                tail = set_next(tail, consume_token(buf));
                tail = set_next(tail, spawn_token(NULL, NULL, subtract));
                continue;
        }
        push_char(buf, input);
        prev = input;
    }
    tail = set_next(tail, consume_token(buf));
    return destroy_token(head);
}

static long gcf(long a, long b) {
    while(a > 0 && b > 0) {
        if(a > b)
            a %= b;
        else
            b %= a;
    }
    return a | b;
}

number_t newnum(const long num, const long den) {
    number_t out = {num, den};
    return out;
}

number_t simplify(const number_t this) {
    long factor;
    if(this.den == 0) {
        fprintf(stderr, "ERROR: Zero division! %ld/%ld\n", this.num, this.den);
        return this;
    }
    if(this.num%this.den == 0)
        return newnum(this.num/this.den, 1);
    factor = gcf(this.num, this.den);
    return newnum(this.num/factor, this.den/factor);
}

number_t sum_or_diff(const number_t left,
                     const number_t right,
                     const long mult) {
    long tmp = 1;
    number_t out = {left.num, left.den};
    if(out.den != right.den) {
        out.num *= right.den;
        out.den *= right.den;
        tmp = left.den;
    }
    out.num += right.num * tmp * mult;
    return out;
}

number_t prod_or_quot(const number_t left, const number_t right, const int div) {
    number_t out = newnum(left.num, left.den);
    if(left.num == 0 || right.num == 0)
        return newnum(0, 1);
    out.num *= (div) ? right.den : right.num;
    out.den *= (div) ? right.num : right.den;
    return out;
}

number_t consume_num(const char *src, const int proceed) {
    number_t out = {0, 1};
    char *endptr;
    if(!*src)
        return out;
    out.num = strtol(src, &endptr, 10);
    if(!*endptr)
        return out;
    if(*endptr=='_' && proceed)
        return sum_or_diff(out, consume_num(endptr+1, 0), 1);
    if(*endptr=='/' && *++endptr)
        out.den = strtol(endptr, NULL, 10);
    return out;
}


int process_tokens(token_t *head) {
    token_t *cur = head;
    number_t total = newnum(0, 1);
    operator_t op = add;
    if(!head)
        return 0;
    while(cur) {
        if(cur->op == none)
            switch (op) {
                case add: case subtract:
                    total = sum_or_diff(total, consume_num(cur->content, 1), (op==add) ? 1 : -1);
                    break;
                case multiply: case divide:
                    total = prod_or_quot(total, consume_num(cur->content, 1), op==divide);
                    break;
                default:
                    printf("Unknown operation: %s\n", cur->content);
                    obliterate_token_chain(cur);
                    return 0;
            }
        else
            op = cur->op;
        cur = destroy_token(cur);
    }
    printf("= ");
    show(simplify(total));
    return 1;
}

void repl(FILE *src) {
    buffer_t *buf = spawn_buffer(STARTING_BUFFER_SIZE);
    while(process_tokens(read_stream(src, buf)));
    delete_buffer(buf);
}

int main(void) {
    repl(stdin);
    return 0;
}

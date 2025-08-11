#include "shell.h"

token_t *tokenize(const char *input, int *token_count) {
    /* TODO: Implement in Phase 2 */
    (void)input;
    *token_count = 0;
    return NULL;
}

void free_tokens(token_t *tokens, int count) {
    /* TODO: Implement in Phase 2 */
    (void)tokens;
    (void)count;
}

char *expand_variables(const char *input) {
    /* TODO: Implement in Phase 2 */
    return strdup(input);
}

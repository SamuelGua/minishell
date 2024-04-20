#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NO_QUOTE 0
#define S_QUOTE 1
#define D_QUOTE 2

int is_quoted(int quoted, char c)
{
    if (quoted == NO_QUOTE && c == '\'')
        return S_QUOTE;
    else if (quoted == NO_QUOTE && c == '\"')
        return D_QUOTE;
    else if (quoted == S_QUOTE && c == '\'')
        return NO_QUOTE;
    else if (quoted == D_QUOTE && c == '\"')
        return NO_QUOTE;
    return quoted;
}

char *remove_unquoted_quotes(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    int len = strlen(str);
    if (len < 2 || (str[0] != '\"' && str[len - 1] != '\"')) {
        // If the string is too short or doesn't start and end with double quotes,
        // return a copy of the input string
        char *new_str = (char *)malloc(len + 1);
        if (new_str == NULL) {
            return NULL;
        }
        strcpy(new_str, str);
        return new_str;
    }

    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }

    int quoted_single = NO_QUOTE;
    int quoted_double = D_QUOTE; // Start with quoted_double since the whole string is inside double quotes
    int j = 0;

    for (int i = 0; i < len; i++) {
        if ((quoted_single != NO_QUOTE && str[i] == '\'') || (quoted_double != NO_QUOTE && str[i] == '\"')) {
            new_str[j++] = str[i];
        } else if (str[i] != '\'' && str[i] != '\"') {
            new_str[j++] = str[i];
        }

        if (str[i] == '\'') {
            quoted_single = is_quoted(quoted_single, str[i]);
        } else if (str[i] == '\"') {
            quoted_double = is_quoted(quoted_double, str[i]);
        }
    }

    new_str[j] = '\0';
    return new_str;
}

int main() {
    char *input = "\"tres'dos'tres\"";
    char *output = remove_unquoted_quotes(input);
    printf("Input: %s\n", input);
    printf("Output: %s\n", output);
    free(output);
    return 0;
}

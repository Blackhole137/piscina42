#include <stdlib.h>

static size_t ft_strlen(char *s)
{
    size_t len = 0;

    while (s && s[len])
        len++;
    return (len);
}

static int starts_with(char *s, char *sep)
{
    while (*sep)
    {
        if (*s != *sep)
            return (0);
        s++;
        sep++;
    }
    return (1);
}

static size_t count_tokens(char *str, char *charset)
{
    size_t count = 0;
    size_t sep_len = ft_strlen(charset);

    if (!str || !charset)
        return (0);
    if (sep_len == 0)
        return (*str ? 1 : 0);
    while (*str)
    {
        while (*str && starts_with(str, charset))
            str += sep_len;
        if (!*str)
            break;
        count++;
        while (*str && !starts_with(str, charset))
            str++;
    }
    return (count);
}

static char *copy_token(char *start, size_t len)
{
    char *token = malloc(len + 1);
    size_t i;

    if (!token)
        return (NULL);
    i = 0;
    while (i < len)
    {
        token[i] = start[i];
        i++;
    }
    token[i] = '\0';
    return (token);
}

static void free_matrix(char **matrix, size_t filled)
{
    size_t i;

    if (!matrix)
        return;
    i = 0;
    while (i < filled)
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

char **ft_split(char *str, char *charset)
{
    char **result;
    size_t token_count;
    size_t sep_len;
    size_t index;
    char *start;

    if (!str || !charset)
        return (NULL);
    sep_len = ft_strlen(charset);
    token_count = count_tokens(str, charset);
    result = malloc(sizeof(char *) * (token_count + 1));
    if (!result)
        return (NULL);
    index = 0;
    while (*str && index < token_count)
    {
        while (*str && sep_len && starts_with(str, charset))
            str += sep_len;
        if (!*str)
            break;
        start = str;
        while (*str && !(sep_len && starts_with(str, charset)))
            str++;
        result[index] = copy_token(start, (size_t)(str - start));
        if (!result[index])
        {
            free_matrix(result, index);
            return (NULL);
        }
        index++;
    }
    result[index] = NULL;
    return (result);
}

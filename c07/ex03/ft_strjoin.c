#include <stdlib.h>

char *ft_strjoin(int size, char **strs, char *sep)
{
    int i;
    int j;
    int total_length;
    char *result;

    if (size <= 0)
    {
        result = (char *)malloc(sizeof(char));
        if (!result)
            return (NULL);
        result[0] = '\0';
        return (result);
    }

    total_length = 0;
    for (i = 0; i < size; i++)
        total_length += strlen(strs[i]);
    total_length += (size - 1) * strlen(sep);

    result = (char *)malloc(sizeof(char) * (total_length + 1));
    if (!result)
        return (NULL);

    result[0] = '\0';
    for (i = 0; i < size; i++)
    {
        strcat(result, strs[i]);
        if (i < size - 1)
            strcat(result, sep);
    }
    return (result);
}
#include <stdlib.h>
#include "../ex05/ft_stock_str.h"

static int ft_strlen(char *str)
{
    int len = 0;

    while (str && str[len])
        len++;
    return len;
}

static char *ft_strdup(char *src)
{
    int len = ft_strlen(src);
    char *dup = malloc((len + 1) * sizeof(char));
    int i;

    if (!dup)
        return NULL;
    i = 0;
    while (i <= len)
    {
        dup[i] = src[i];
        i++;
    }
    return dup;
}

struct s_stock_str *ft_strs_to_tab(int ac, char **av)
{
    t_stock_str *tab;
    int i;

    tab = malloc((ac + 1) * sizeof(t_stock_str));
    if (!tab)
        return NULL;
    i = 0;
    while (i < ac)
    {
        tab[i].size = ft_strlen(av[i]);
        tab[i].str = av[i];
        tab[i].copy = ft_strdup(av[i]);
        if (!tab[i].copy)
        {
            while (i-- > 0)
                free(tab[i].copy);
            free(tab);
            return NULL;
        }
        i++;
    }
    tab[ac].size = 0;
    tab[ac].str = 0;
    tab[ac].copy = 0;
    return tab;
}
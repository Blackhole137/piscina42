int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_sort_string_tab(char **tab)
{
    int     i;
    char    *temp;

    if (!tab)
        return ;
    i = 0;
    while (tab[i] && tab[i + 1])
    {
        if (ft_strcmp(tab[i], tab[i + 1]) > 0)
        {
            temp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = temp;
            i = -1;
        }
        i++;
    }
}
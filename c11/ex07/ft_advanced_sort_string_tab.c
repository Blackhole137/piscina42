void ft_advanced_sort_string_tab(char **tab, int(*cmp)(char *, char *))
{
    int     i;
    char    *temp;

    if (!tab || !cmp)
        return ;
    i = 0;
    while (tab[i] && tab[i + 1])
    {
        if (cmp(tab[i], tab[i + 1]) > 0)
        {
            temp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = temp;
            i = -1;
        }
        i++;
    }
}
int ft_is_sort(int *tab, int length, int(*f)(int, int))
{
    int i;
    int res;

    if (length < 2)
        return (1);
    i = 0;
    while (i < length - 1)
    {
        res = f(tab[i], tab[i + 1]);
        if (res > 0)
            break ;
        else if (res < 0)
            break ;
        i++;
    }
    while (i < length - 1)
    {
        res = f(tab[i], tab[i + 1]);
        if ((res > 0 && f(tab[i - 1], tab[i]) < 0) ||
            (res < 0 && f(tab[i - 1], tab[i]) > 0))
            return (0);
        i++;
    }
    return (1);
}
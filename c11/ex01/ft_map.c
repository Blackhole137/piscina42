int *ft_map(int *tab, int length, int(*f)(int))
{
    int i;
    int *res;

    res = (int *)malloc(sizeof(int) * length);
    if (!res)
        return (NULL);
    i = 0;
    while (i < length)
    {
        res[i] = f(tab[i]);
        i++;
    }
    return (res);
}
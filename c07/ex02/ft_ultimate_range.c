int ft_ultimate_range(int **range, int min, int max)
{
    int *arr;
    int i;

    if (min >= max)
    {
        *range = NULL;
        return (0);
    }
    arr = (int *)malloc(sizeof(int) * (max - min));
    if (!arr)
    {
        *range = NULL;
        return (-1);
    }
    i = 0;
    while (min < max)
    {
        arr[i] = min;
        i++;
        min++;
    }
    *range = arr;
    return (i);
}

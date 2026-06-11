int ft_sqrt(int nb)
{
    int low;
    int high;
    int mid;
    long long square;

    if (nb <= 1)
        return (nb);
    low = 2;
    high = nb / 2;
    while (low <= high)
    {
        mid = (low + high) / 2;
        square = (long long)mid * mid;
        if (square == nb)
            return (mid);
        if (square < nb)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return (0);
}
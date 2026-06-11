void ft_putnbr_base(int nbr, char *base)
{
    int base_len;
    int i;
    int is_negative;

    base_len = 0;
    while (base[base_len] != '\0')
        base_len++;
    if (base_len < 2)
        return ;
    i = 0;
    while (i < base_len)
    {
        if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] > 126)
            return ;
        if (base[i] == base[0])
            return ;
        int j = i + 1;
        while (j < base_len)
        {
            if (base[i] == base[j])
                return ;
            j++;
        }
        i++;
    }
    is_negative = 0;
    if (nbr < 0)
    {
        is_negative = 1;
        nbr = -nbr;
    }
    char result[32];
    int index = 0;
    while (nbr > 0)
    {
        result[index++] = base[nbr % base_len];
        nbr /= base_len;
    }
    if (is_negative)
        write(1, "-", 1);
    while (index > 0)
        write(1, &result[--index], 1);
}

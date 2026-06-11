int ft_atoi_base(char *str, char *base)
{
    int base_len;
    int i;
    int sign;
    int result;

    base_len = 0;
    while (base[base_len] != '\0')
        base_len++;
    if (base_len < 2)
        return (0);
    i = 0;
    while (i < base_len)
    {
        if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] > 126)
            return (0);
        if (base[i] == base[0])
            return (0);
        int j = i + 1;
        while (j < base_len)
        {
            if (base[i] == base[j])
                return (0);
            j++;
        }
        i++;
    }
    sign = 1;
    result = 0;
    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] != '\0')
    {
        int digit_value = -1;
        for (int k = 0; k < base_len; k++)
        {
            if (str[i] == base[k])
            {
                digit_value = k;
                break;
            }
        }
        if (digit_value == -1)
            break ;
        result = result * base_len + digit_value;
        i++;
    }
    return (result * sign);
}

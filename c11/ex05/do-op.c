#include <unistd.h>

typedef int (*t_op)(int, int);

static int  ft_atoi(const char *str)
{
    int     sign;
    long    value;

    sign = 1;
    value = 0;
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        value = value * 10 + (*str - '0');
        str++;
    }
    return ((int)(value * sign));
}

static void ft_putchar(char c)
{
    write(1, &c, 1);
}

static void ft_putstr(const char *str)
{
    while (*str)
        write(1, str++, 1);
}

static void ft_putnbr(int n)
{
    if (n == -2147483648)
    {
        ft_putstr("-2147483648");
        return;
    }
    if (n < 0)
    {
        ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10);
    ft_putchar((char)('0' + (n % 10)));
}

static int add(int a, int b)
{
    return (a + b);
}

static int sub(int a, int b)
{
    return (a - b);
}

static int mul(int a, int b)
{
    return (a * b);
}

static int divide(int a, int b)
{
    return (a / b);
}

static int modulo(int a, int b)
{
    return (a % b);
}

int main(int argc, char **argv)
{
    struct s_op
n    {
        char    op;
        t_op    f;
    } ops[] = {
        {'+', add},
        {'-', sub},
        {'*', mul},
        {'/', divide},
        {'%', modulo},
    };
    int         i;
    int         a;
    int         b;
    char        op;
    int         result;

    if (argc != 4)
        return (0);
    if (argv[2][0] == '\0' || argv[2][1] != '\0')
    {
        ft_putstr("0");
        return (0);
    }
    op = argv[2][0];
    a = ft_atoi(argv[1]);
    b = ft_atoi(argv[3]);
    if ((op == '/' || op == '%') && b == 0)
    {
        if (op == '/')
            ft_putstr("Stop : division by zero");
        else
            ft_putstr("Stop : modulo by zero");
        return (0);
    }
    i = 0;
    while (i < 5)
    {
        if (ops[i].op == op)
        {
            result = ops[i].f(a, b);
            ft_putnbr(result);
            ft_putchar('\n');
            return (0);
        }
        i++;
    }
    ft_putstr("0");
    return (0);
}

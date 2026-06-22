#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_BUF_SIZE 4096

static size_t ft_strlen(const char *s)
{
    size_t len = 0;

    while (s && s[len])
        len++;
    return (len);
}

static void ft_putstr_fd(const char *s, int fd)
{
    if (!s)
        return;
    write(fd, s, ft_strlen(s));
}

static long ft_atol(const char *s)
{
    long result = 0;

    if (!s || !*s)
        return (-1);
    while (*s >= '0' && *s <= '9')
    {
        result = result * 10 + (*s - '0');
        s++;
    }
    if (*s != '\0')
        return (-1);
    return (result);
}

static void print_error(const char *program, const char *name)
{
    char *prog_name;

    prog_name = basename((char *)program);
    if (prog_name)
        ft_putstr_fd(prog_name, STDERR_FILENO);
    else
        ft_putstr_fd("ft_tail", STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    if (name)
    {
        ft_putstr_fd(name, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putstr_fd(strerror(errno), STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

static int write_tail_buffer(char *buf, long count, long total, long start)
{
    long i;

    if (count <= 0 || total <= 0)
        return (0);
    if (total <= count)
        return ((int)write(STDOUT_FILENO, buf, (size_t)total));
    i = start;
    while (i < count)
    {
        if (write(STDOUT_FILENO, buf + i, 1) < 0)
            return (-1);
        i++;
    }
    i = 0;
    while (i < start)
    {
        if (write(STDOUT_FILENO, buf + i, 1) < 0)
            return (-1);
        i++;
    }
    return (0);
}

static int tail_fd(int fd, long count)
{
    char *buf;
    char tmp[READ_BUF_SIZE];
    ssize_t bytes_read;
    long total;
    long pos;
    long idx;

    if (count <= 0)
        return (0);
    buf = malloc((size_t)count);
    if (!buf)
        return (-1);
    total = 0;
    pos = 0;
    while ((bytes_read = read(fd, tmp, READ_BUF_SIZE)) > 0)
    {
        idx = 0;
        while (idx < bytes_read)
        {
            if (count > 0)
                buf[pos] = tmp[idx];
            pos = (pos + 1) % count;
            idx++;
            if (total < count)
                total++;
        }
    }
    if (bytes_read < 0)
    {
        free(buf);
        return (-1);
    }
    if (write_tail_buffer(buf, count, total, pos) < 0)
    {
        free(buf);
        return (-1);
    }
    free(buf);
    return (0);
}

static int process_file(const char *program, const char *file_name,
        long count, int show_header)
{
    int fd;
    int status;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        print_error(program, file_name);
        return (1);
    }
    if (show_header)
    {
        ft_putstr_fd("==> ", STDOUT_FILENO);
        ft_putstr_fd((char *)file_name, STDOUT_FILENO);
        ft_putstr_fd(" <==\n", STDOUT_FILENO);
    }
    status = tail_fd(fd, count);
    if (close(fd) < 0)
        status = -1;
    if (status < 0)
    {
        print_error(program, file_name);
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    long count;
    int file_count;
    int i;
    int exit_status;

    if (argc < 3 || strcmp(argv[1], "-c") != 0)
    {
        ft_putstr_fd("usage: ", STDERR_FILENO);
        ft_putstr_fd(argv[0], STDERR_FILENO);
        ft_putstr_fd(" -c byte_count [file ...]\n", STDERR_FILENO);
        return (1);
    }
    count = ft_atol(argv[2]);
    if (count < 0)
    {
        ft_putstr_fd("ft_tail: invalid number of bytes\n", STDERR_FILENO);
        return (1);
    }
    file_count = argc - 3;
    exit_status = 0;
    if (file_count == 0)
    {
        if (tail_fd(STDIN_FILENO, count) < 0)
        {
            print_error(argv[0], NULL);
            return (1);
        }
        return (0);
    }
    i = 3;
    while (i < argc)
    {
        if (process_file(argv[0], argv[i], count, file_count > 1) != 0)
            exit_status = 1;
        if (i + 1 < argc && file_count > 1)
            ft_putstr_fd("\n", STDOUT_FILENO);
        i++;
    }
    return (exit_status);
}

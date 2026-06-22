#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 30000

static char g_buffer[BUFFER_SIZE];

static size_t ft_strlen(const char *s)
{
    size_t len = 0;

    while (s && s[len])
        len++;
    return (len);
}

static ssize_t ft_write_all(int fd, const void *buf, size_t count)
{
    ssize_t written;
    size_t total;
    const char *data;

    data = buf;
    total = 0;
    while (total < count)
    {
        written = write(fd, data + total, count - total);
        if (written <= 0)
            return (-1);
        total += (size_t)written;
    }
    return ((ssize_t)total);
}

static void ft_putstr_fd(const char *s, int fd)
{
    if (!s)
        return;
    ft_write_all(fd, s, ft_strlen(s));
}

static void ft_putendl_fd(const char *s, int fd)
{
    ft_putstr_fd(s, fd);
    write(fd, "\n", 1);
}

static void ft_print_error(const char *file)
{
    char *basename_name;

    basename_name = basename((char *)file);
    if (!basename_name)
        basename_name = (char *)file;
    ft_putstr_fd("ft_cat: ", 2);
    ft_putstr_fd(basename_name, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putendl_fd("", 2);
}

static int cat_fd(int fd)
{
    ssize_t read_bytes;

    while (1)
    {
        read_bytes = read(fd, g_buffer, BUFFER_SIZE);
        if (read_bytes == 0)
            return (0);
        if (read_bytes < 0)
            return (-1);
        if (ft_write_all(1, g_buffer, (size_t)read_bytes) < 0)
            return (-1);
    }
}

static int cat_file(const char *filename)
{
    int fd;
    int result;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_print_error(filename);
        return (-1);
    }
    result = cat_fd(fd);
    if (result < 0)
        ft_print_error(filename);
    close(fd);
    return (result);
}

int main(int argc, char **argv)
{
    int index;
    int status;

    status = 0;
    if (argc == 1)
    {
        if (cat_fd(0) < 0)
            return (1);
        return (0);
    }
    index = 1;
    while (index < argc)
    {
        if (cat_file(argv[index]) < 0)
            status = 1;
        index++;
    }
    return (status);
}

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int fd;
    ssize_t bytes_read;
    static char buffer[BUF_SIZE];

    if (argc != 2)
        return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (1);
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(1, buffer, bytes_read) != bytes_read)
        {
            close(fd);
            return (1);
        }
    }
    close(fd);
    if (bytes_read < 0)
        return (1);
    return (0);
}


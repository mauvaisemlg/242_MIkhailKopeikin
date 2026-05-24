#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fd;
    int i;
    int x;
    int y;
    long a;
    struct stat st;
    char s[4096];

    if (argc != 2)
    {
        write(2, "wrong arguments\n", 16);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        write(2, "cannot open file\n", 17);
        return 1;
    }

    if (fstat(fd, &st) < 0)
    {
        write(2, "fstat error\n", 12);
        close(fd);
        return 1;
    }

    if (st.st_size <= 0)
    {
        close(fd);
        return 0;
    }

    a = st.st_size / 2;

    if (lseek(fd, a, SEEK_SET) < 0)
    {
        write(2, "lseek error\n", 12);
        close(fd);
        return 1;
    }

    if (st.st_size - a < 4096)
        y = st.st_size - a;
    else
        y = 4096;

    while ((x = read(fd, s, y)) > 0)
    {
        for (i = 0; i < x; i++)
        {
            if (s[i] == '\n')
            {
                write(1, s, i + 1);
                close(fd);
                return 0;
            }
        }

        write(1, s, x);
    }

    close(fd);

    return 0;
}
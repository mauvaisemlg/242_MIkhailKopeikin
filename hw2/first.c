#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    int i;
    int x;
    int y;
    int l;
    long a;
    long b;
    long c;
    long d;
    struct stat st;
    char s[4096];

    if (argc != 4)
    {
        write(2, "wrong arguments\n", 16);
        return 1;
    }

    a = atol(argv[2]);
    b = atol(argv[3]);

    if (a <= 0 || b <= 0)
    {
        write(2, "wrong numbers\n", 14);
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

    if (st.st_size < 4096)
        y = st.st_size;
    else
        y = 4096;

    if (y <= 0)
    {
        close(fd);
        return 0;
    }

    c = 1;
    d = 0;

    while (d < b && (x = read(fd, s, y)) > 0)
    {
        l = 0;

        for (i = 0; i < x && d < b; i++)
        {
            if (s[i] == '\n')
            {
                if (c >= a)
                {
                    write(1, s + l, i - l + 1);
                    d++;
                }

                c++;
                l = i + 1;
            }
        }

        if (d < b && l < x && c >= a)
        {
            write(1, s + l, x - l);
        }
    }

    close(fd);

    return 0;
}
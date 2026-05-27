#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[])
{
    regex_t r;
    regmatch_t m;

    char *a;
    char *b;
    char *c;
    char *d;
    char *e;

    int x;
    int y;

    size_t i;
    size_t n;
    size_t k;

    if (argc != 4)
    {
        return 1;
    }

    a = argv[1];
    b = argv[2];
    c = argv[3];

    if (regcomp(&r, a, REG_EXTENDED) != 0)
    {
        return 1;
    }

    n = strlen(b) + strlen(c) + 100;
    d = malloc(n);

    if (d == NULL)
    {
        regfree(&r);
        return 1;
    }

    e = b;
    k = 0;

    while (regexec(&r, e, 1, &m, 0) == 0)
    {
        x = m.rm_so;
        y = m.rm_eo;

        while (k + x + strlen(c) + 2 >= n)
        {
            n = n * 2;
            d = realloc(d, n);

            if (d == NULL)
            {
                regfree(&r);
                return 1;
            }
        }

        for (i = 0; i < (size_t)x; i++)
        {
            d[k] = e[i];
            k++;
        }

        for (i = 0; i < strlen(c); i++)
        {
            d[k] = c[i];
            k++;
        }

        if (x == y)
        {
            if (e[0] == '\0')
            {
                break;
            }

            d[k] = e[0];
            k++;
            e++;
        }
        else
        {
            e = e + y;
        }
    }

    while (k + strlen(e) + 1 >= n)
    {
        n = n * 2;
        d = realloc(d, n);

        if (d == NULL)
        {
            regfree(&r);
            return 1;
        }
    }

    for (i = 0; i < strlen(e); i++)
    {
        d[k] = e[i];
        k++;
    }

    d[k] = '\0';

    printf("%s\n", d);

    free(d);
    regfree(&r);

    return 0;
}
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THREADS 4

struct Data {
    int left;
    int right;
};

int *a;
long long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *work(void *arg)
{
    struct Data *data = arg;
    long long part = 0;

    for (int i = data->left; i < data->right; i++) {
        part += a[i];
    }

    pthread_mutex_lock(&mutex);
    sum += part;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    int n;
    pthread_t threads[THREADS];
    struct Data data[THREADS];

    if (scanf("%d", &n) != 1 || n < 16) {
        return 1;
    }

    a = malloc(n * sizeof(int));
    if (a == NULL) {
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    for (int i = 0; i < THREADS; i++) {
        data[i].left = i * n / THREADS;
        data[i].right = (i + 1) * n / THREADS;

        if (pthread_create(&threads[i], NULL, work, &data[i]) != 0) {
            free(a);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("%lld\n", sum);

    pthread_mutex_destroy(&mutex);
    free(a);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int x;
    struct Node *next;
};

int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;

    while (1) {
        int x;
        scanf("%d", &x);

        if (x == 0) {
            break;
        }

        struct Node *p = (struct Node *)malloc(sizeof(struct Node));
        if (p == NULL) {
            return 1;
        }

        p->x = x;
        p->next = NULL;

        if (head == NULL) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }

    struct Node *prev = NULL;
    struct Node *cur = head;

    while (cur != NULL) {
        struct Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head = prev;

    struct Node *p = head;
    while (p != NULL) {
        printf("%d ", p->x);
        p = p->next;
    }
    printf("\n");

    p = head;
    while (p != NULL) {
        struct Node *next = p->next;
        free(p);
        p = next;
    }

    return 0;
}
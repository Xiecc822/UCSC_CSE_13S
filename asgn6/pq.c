#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {

    Node *tree;
    ListElement *next;
};

struct PriorityQueue {

    ListElement *list;
};

PriorityQueue *pq_create(void) {

    PriorityQueue *new_queue = (PriorityQueue *) calloc(1, sizeof(PriorityQueue));
    return new_queue;
}

void pq_free(PriorityQueue **q) {

    if (*q == NULL) {

        return;
    }

    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {

    return q->list == NULL;
}

bool pq_size_is_1(PriorityQueue *q) {

    return (q != NULL) && (q->list != NULL) && (q->list->next == NULL);
}

void enqueue(PriorityQueue *q, Node *tree) {

    ListElement *new_element = (ListElement *) malloc(sizeof(ListElement));
    new_element->tree = tree;

    if (q->list == NULL) {

        q->list = new_element;

    } else if (tree->weight < q->list->tree->weight) {

        new_element->next = q->list;
        q->list = new_element;

    } else {

        ListElement *current = q->list;
        while (current->next != NULL && current->next->tree->weight <= tree->weight) {

            current = current->next;
        }

        new_element->next = current->next;
        current->next = new_element;
    }
}

bool dequeue(PriorityQueue *q, Node **tree) {

    if (q == NULL || q->list == NULL) {

        return false;
    }

    ListElement *element = q->list;
    q->list = element->next;
    *tree = element->tree;
    free(element);

    return true;
}

void pq_print(PriorityQueue *q) {

    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {

        if (position++ == 1) {

            printf("========================================\n");

        } else {

            printf("----------------------------------------\n");
        }

        node_print_tree(e->tree, '<', 2);
        e = e->next;
    }

    printf("========================================\n");
}

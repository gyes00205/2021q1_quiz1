#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>  
#include <time.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

static inline void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right: &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot); 
    list_concat(&result, right);
    *list = result;
}

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

static void list_free(node_t **list) {
    while (*list) {
        node_t *tmp = *list;
        *list = (*list)->next;
        free(tmp);
    }
}

node_t *list_make_node_t(node_t *list, int value) {
    node_t *head = list;
    node_t *tmp;    
    if (!list) {
        list = (node_t*)malloc(sizeof(node_t));
        list->next = NULL;
        list->value = value;
        return list;
    }

    while (list->next)
        list = list->next;

    tmp = (node_t*)malloc(sizeof(node_t));
    tmp->next = NULL;
    tmp->value = value;
    list->next = tmp;
    return head;
}

int find_value(node_t *list, int index) {
    while (index--)
        list = list->next;
    return list->value;    
}

void assign_value(node_t *list, int index, int value) {
    while (index--)
        list = list->next;
    list->value = value;    
}

bool quicksort_iterative(node_t **list, int elements) {
    #define MAX_LEVELS  1000

    int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i=0, L, R ;
    beg[0]=0; end[0]=elements;
    while (i >= 0) {
        L=beg[i]; R=end[i]-1;
        if (L < R) {
            piv = find_value(*list, L);
            if (i == MAX_LEVELS-1) 
                return false;
            while (L < R) {
                while (find_value(*list, R) >= piv && L < R) 
                    R--; 
                if (L < R) 
                    assign_value(*list, L++, find_value(*list, R));
                while (find_value(*list, L) <= piv && L < R) 
                    L++; 
                if (L < R) 
                    assign_value(*list, R--, find_value(*list, L));
            }
            assign_value(*list, L, piv); beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L; 
        }
        else
            i--;
    }
    return true; 
}

int main(int argc, char **argv) {
    size_t count = 20;
    bool success;
    node_t *list = NULL;
    srandom(time(NULL));
    for (int i = 0; i < count; i++)
        list = list_make_node_t(list, random() % 1024);
    list_display(list);
    success = quicksort_iterative(&list, count);
    if(!success)
        return EXIT_FAILURE;
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}        
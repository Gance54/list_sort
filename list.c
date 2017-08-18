#include <list.h>
#include <malloc.h>
#include <log.h>
struct node
{
    void *data;
    struct list *list;
    struct node *next;
    struct node *prev;
};

struct list
{
    struct node *head;
    struct node *tail;
    int total;
    delete_cb_t delete_cb;
    print_cb_t print_cb;
};

list_t *list_create(delete_cb_t delete_cb, print_cb_t print_cb)
{
    list_t *l = malloc(sizeof(struct list));
    if(l)
        memset(l, 0, sizeof(struct list));

    l->delete_cb = delete_cb;
    l->print_cb = print_cb;
    return l;
}

struct node *s_node_create(struct list *list, void *data)
{
    struct node *n = malloc(sizeof(struct node));
    if(!n) return NULL;

    memset(n, 0, sizeof(*n));
    n->data = data;
    n->list = list;

    if(list)
    {
        if(!list->head)
            list->head = n;

        if(!list->tail)
            list->tail = n;
    }

    return n;
}

int list_add_tail(list_t *l, void *data)
{
    struct node *n = s_node_create(l, data);
    if(!n) return -1;

    n->prev = l->tail;

    l->tail->next = n;
    l->tail = n;
    l->total++;

    return 0;
}

int list_add_head(list_t *l, void *data)
{
    struct node *n = s_node_create(l, data);
    if(!n) return -1;

    n->next = l->head;

    l->head->prev = n;
    l->head = n;
    l->total++;

    return 0;
}

node_t *list_get_tail(list_t *l)
{
    return l->tail;
}

node_t *list_get_head(list_t *l)
{
    return l->head;
}

int list_get_count(list_t *l)
{
    return l->total;
}

void list_delete(list_t *l, node_t *node)
{
    if(!node->prev && !node->next)
        l->head = l->tail = NULL;
    else
    {
        if(!node->prev)
            l->head = l->head->next;
        else
            node->prev->next = node->next;

        if(!node->next)
            l->tail = l->tail->prev;
        else
            node->next->prev = node->prev;
    }

    if(node->data && l->delete_cb)
        l->delete_cb(node->data);

    free(node);

    l->total--;
}

void list_clear(list_t *l)
{
    struct node *n = l->head;

    while(n)
    {
        struct node *tmp = n;
        n = n->next;

        if(l->delete_cb)
            l->delete_cb(tmp->data);

        free(tmp);
    }

    memset(l, 0, sizeof(*l));
}

void list_destroy(list_t **l)
{
    list_clear(*l);
    free(*l);
    *l = NULL;
}

void list_print(list_t *l)
{
    struct node *n = l->head;

    if(!l->print_cb)
    {
        LOGE("Can't print list. No print callback");
        return;
    }

    while(n)
    {
        l->print_cb(n->data);
        n = n->next;
    }
}

void *node_get_data(node_t *node)
{
    return node->data;
}

void node_set_data(node_t *node, void *data)
{
    if(node->data)
    {
        if(!node->list || !node->list->delete_cb)
        {
            LOGW("Can not change the data in node without loosing memory. "
                 "No deleting callback");
            return;
        }

        node->list->delete_cb(node->data);
    }

    node->data = data;
}

node_t *node_next(node_t *node)
{
    return node->next;
}

node_t *node_prev(node_t *node)
{
    return node->prev;
}

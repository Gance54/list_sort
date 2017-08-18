#ifndef LIST_H
#define LIST_H
typedef struct list list_t;
typedef struct node node_t;

typedef void (*delete_cb_t)(void *);
typedef void (*print_cb_t)(void *);

list_t *list_create(delete_cb_t delete_cb, print_cb_t print_cb);

int list_add_head(list_t *l, void *data);
int list_add_tail(list_t *l, void *data);

node_t *list_get_head(list_t *l);
node_t *list_get_tail(list_t *l);
int list_get_count(list_t *l);

void list_delete(list_t *l, node_t *node);
void list_clear(list_t *l);
void list_destroy(list_t **l);

void list_print(list_t *l);

void *node_get_data(node_t *node);
void node_set_data(node_t *node, void *data);
node_t *node_next(node_t *node);
node_t *node_prev(node_t *node);
#endif // LIST_H

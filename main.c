#include <stdio.h>
#include <list.h>
#include <log.h>
#include <malloc.h>

void prnt(int *n)
{
    LOGD("Number %d", *n);
}

int main(void)
{
    list_t *l = list_create(free, (print_cb_t)prnt);
    if(!l)
    {
        LOGE("Failed to allocate memory");
        return -1;
    }

    for(int i = 0; i < 100; i++)
    {
        int *el = malloc(sizeof(int));
        *el = i;
        if(i%2)
            list_add_tail(l, el);
        else
            list_add_head(l, el);
    }

    list_print(l);
    list_destroy(&l);

    return 0;
}

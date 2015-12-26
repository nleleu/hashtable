#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lru_table.h"

lru_table_Ts* lru_table_init(size_t len)
{
    lru_table_Ts* lru_struct = (lru_table_Ts*)malloc(sizeof(lru_table_Ts));
    lru_struct->lru_table = (list_entry_Ts*)malloc(len * sizeof(list_entry_Ts));
    lru_struct->len = len;
    size_t i;
    TAILQ_HEAD(lru_list, list_entry_Ts) toto;
    TAILQ_INIT(&toto);
    lru_struct->nb_item = 0;
    for(i = 0; i < len; i++)
    {
        lru_struct->lru_table[i].key.len = 0;
        TAILQ_INSERT_HEAD(&(lru_struct->lru_head), &(lru_struct->lru_table[i]), next);
    }
    return lru_struct;
}


void lru_table_delete(lru_table_Ts* lru_struct, buffer_Ts* buffer)
{
    size_t i;
    for(i = 0; i < lru_struct->len ; i++)
    {
        if (lru_struct->lru_table[i].key.len == buffer->len && memcmp(lru_struct->lru_table[i].key.data, buffer->data, buffer->len) == 0)
        {
            printf("Delete %.*s at index %zu\n", (int)buffer->len, buffer->data, i);
            free(lru_struct->lru_table[i].key.data);
            lru_struct->lru_table[i].key.len = 0;
            lru_struct->nb_item --;
            TAILQ_REMOVE(&(lru_struct->lru_head), &(lru_struct->lru_table[i]), next);
            TAILQ_INSERT_TAIL(&(lru_struct->lru_head), &(lru_struct->lru_table[i]), next);
        }
    }
}

list_entry_Ts* lru_table_lookup(lru_table_Ts* lru_struct, buffer_Ts* buffer)
{
    size_t i;
    for(i = 0; i < lru_struct->len ; i++)
    {
        if (lru_struct->lru_table[i].key.len == buffer->len && memcmp(lru_struct->lru_table[i].key.data, buffer->data, buffer->len) == 0)
        {
            printf("Found %.*s at index %zu\n", (int)buffer->len, buffer->data, i);
            TAILQ_REMOVE(&(lru_struct->lru_head), &(lru_struct->lru_table[i]), next);
            TAILQ_INSERT_HEAD(&(lru_struct->lru_head), &(lru_struct->lru_table[i]), next);
            return &(lru_struct->lru_table[i]);
        }
    }

    list_entry_Ts * last = TAILQ_LAST(&(lru_struct->lru_head), lru_list);
    if (last &&  last->key.len > 0)
    {
        printf("Reuse key %.*s. Replace by %.*s\n", (int)last->key.len, last->key.data, (int)buffer->len, buffer->data);
        free(last->key.data);
    }
    else
    {
        printf("New slot for %.*s\n", (int)buffer->len, buffer->data);
        lru_struct->nb_item ++;
    }
    last->key.data = (char*)malloc(buffer->len);
    memcpy(last->key.data, buffer->data, buffer->len);
    last->key.len = buffer->len;
    TAILQ_REMOVE(&(lru_struct->lru_head), last, next);
    TAILQ_INSERT_HEAD(&(lru_struct->lru_head), last, next);
    return last;
}



void lru_table_display(lru_table_Ts* lru_struct)
{
    list_entry_Ts * item;
    TAILQ_FOREACH(item, &(lru_struct->lru_head), next) {
    if (item->key.len)
            printf("Key %.*s\n", (int)item->key.len, item->key.data);
    else
        return;
    }
}
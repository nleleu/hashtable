#ifndef LRU_TABLE_H
#define LRU_TABLE_H
#include <sys/queue.h>
#include <stdlib.h>
#include "utils.h"

typedef struct list_entry_s
{
    TAILQ_ENTRY(list_entry_s) next;
    buffer_Ts key;
}list_entry_Ts;

typedef struct lru_table_s
{
    list_entry_Ts* lru_table;
    size_t len;
    size_t nb_item;
    TAILQ_HEAD(lru_list, list_entry_s) lru_head;
}lru_table_Ts;


lru_table_Ts* lru_table_init(size_t len);

void lru_table_delete(lru_table_Ts* lru_struct, buffer_Ts* buffer);

list_entry_Ts* lru_table_lookup(lru_table_Ts* lru_struct, buffer_Ts* buffer);

void lru_table_display(lru_table_Ts* lru_struct);

#endif

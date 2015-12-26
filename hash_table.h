#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

#include "utils.h"
#include "lru_table.h"


typedef struct hashtable_s
{
    lru_table_Ts** buckets;
    size_t len;
} hashtable_Ts;

hashtable_Ts* hashtable_init(size_t len, size_t bucket_len);

list_entry_Ts* hashtable_lookup(hashtable_Ts*  hashtable_struct, buffer_Ts* buffer);

void hashtable_delete(hashtable_Ts*  hashtable_struct, buffer_Ts* buffer);

void hashtable_display(hashtable_Ts* hashtable_struct);

#endif
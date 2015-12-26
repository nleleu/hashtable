#include "hash_table.h" 
#include <stdio.h>
#define MURMUR_SEED 1337


hashtable_Ts* hashtable_init(size_t len, size_t bucket_len)
{
    hashtable_Ts*  hashtable_struct = (hashtable_Ts*)malloc(sizeof(hashtable_Ts));
    hashtable_struct->buckets = (lru_table_Ts**)malloc(len * sizeof(lru_table_Ts*));
    hashtable_struct->len = len;
    size_t i;
    for(i = 0; i < len; i++)
            hashtable_struct->buckets[i]  = lru_table_init(bucket_len);
    return  hashtable_struct;
}

list_entry_Ts* hashtable_lookup(hashtable_Ts*  hashtable_struct, buffer_Ts* buffer)
{
    uint32_t hash = murmur3_32(buffer->data, buffer->len, MURMUR_SEED);
    size_t idx;
    idx = hash % hashtable_struct->len;
    lru_table_lookup(hashtable_struct->buckets[idx], buffer);
}


void hashtable_delete(hashtable_Ts*  hashtable_struct, buffer_Ts* buffer)
{
    uint32_t hash = murmur3_32(buffer->data, buffer->len, MURMUR_SEED);
    size_t idx;
    idx = hash % hashtable_struct->len;
    lru_table_delete(hashtable_struct->buckets[idx], buffer);
}

void hashtable_display(hashtable_Ts* hashtable_struct)
{
    size_t i;
    for(i = 0; i < hashtable_struct->len; i++)
    {
        if (hashtable_struct->buckets[i]->nb_item > 0)
        {
            printf("Len %zu",hashtable_struct->buckets[i]->nb_item );
            printf("---------------------Bucket id %zu---------------------\n", i);
            lru_table_display(hashtable_struct->buckets[i]);
            printf("------------------------------------------------------\n");
        }
    }
}
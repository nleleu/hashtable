
#include "lru_table.h"
#include "hash_table.h"

int main()
{
    buffer_Ts b1 = {"key1", 4};
    buffer_Ts b2 = {"key2", 4};
    buffer_Ts b3 = {"key3", 4};
    buffer_Ts b4 = {"key4", 4};
    buffer_Ts b5 = {"key5", 4};
    buffer_Ts b6 = {"key6", 4};
    lru_table_Ts* lru_struct =  lru_table_init(3);
    lru_table_lookup(lru_struct, &b1);
    lru_table_lookup(lru_struct, &b1);
    lru_table_lookup(lru_struct, &b2);
    lru_table_lookup(lru_struct, &b3);
    lru_table_lookup(lru_struct, &b4);
    lru_table_lookup(lru_struct, &b5);
    lru_table_lookup(lru_struct, &b5);
    lru_table_delete(lru_struct, &b5);
    lru_table_lookup(lru_struct, &b6);
    lru_table_lookup(lru_struct, &b6);
    lru_table_display(lru_struct);
    hashtable_Ts* hashtable_struct =  hashtable_init(2, 300);
    hashtable_lookup(hashtable_struct, &b1);
    hashtable_lookup(hashtable_struct, &b2);
    hashtable_lookup(hashtable_struct, &b3);
    hashtable_lookup(hashtable_struct, &b4);
    hashtable_lookup(hashtable_struct, &b5);
    hashtable_lookup(hashtable_struct, &b5);
    hashtable_delete(hashtable_struct, &b5);
    hashtable_lookup(hashtable_struct, &b5);
    hashtable_lookup(hashtable_struct, &b5);
    hashtable_display(hashtable_struct);

}

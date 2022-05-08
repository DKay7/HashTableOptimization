#include "hash_functions_to_test.h"
#include "hashtable.h"
#include "utilities.h"
#include "texlib.h"
#include <stdio.h>
#include <locale.h>
#include <assert.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    Text csv_data = {};
    TextCtor (&csv_data, "../data/en-ru.csv");
    const size_t idx_arr_size = 32768;
    int* idx_for_search_array = (int*) calloc (idx_arr_size, sizeof(*idx_for_search_array));

    HashTable<char*, char*> ht = {};
    HashTableCtor<char*, char*> (&ht, 50000, polynimial_rolling_hash, key_equality);

    FillIndexesArrayWithRandomValues (idx_for_search_array, idx_arr_size, csv_data.non_empty_lines);

    FillHashTableFromStrCSV (&csv_data, &ht);

    SearchSpeedTest (idx_for_search_array, idx_arr_size, &ht, &csv_data);

    HashTableDtor (&ht);
    TextDtor (&csv_data);
    free (idx_for_search_array);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second)
{
    return (strcmp (first, second) == 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

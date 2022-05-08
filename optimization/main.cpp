#include "hash_functions_to_test.h"
#include "hashtable.h"
#include "utilities.h"
#include "texlib.h"
#include <stdio.h>
#include <locale.h>
#include <assert.h>
#include <immintrin.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main()
{
    Text csv_data = {};
    TextCtor (&csv_data, "../data/en-ru.csv");
    const size_t idx_arr_size = 262144;
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

bool intrins_key_equality (__m256i* first, __m256i* second)
{
    return _mm256_testc_si256 (_mm256_loadu_si256(first), _mm256_loadu_si256(second));
}
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

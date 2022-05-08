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

int main ()
{   
    setlocale (LC_ALL, "ru_RU.iso88595");
    setlocale (LC_CTYPE, "ru_RU.iso88595");
    setlocale(LC_NUMERIC, "C");

    Text csv_data = {};
    TextCtor (&csv_data, "../data/en-ru.csv");

    #define TEST(func)                                                                  \
    {                                                                                   \
        HashTable<char*, char*> const_size_ht = {};                                     \
        HashTable<char*, char*> var_size_ht = {};                                       \
                                                                                        \
                                                                                        \
        HashTableCtor<char*, char*> (&const_size_ht, 50000, func, key_equality);        \
        HashTableCtor<char*, char*> (&var_size_ht,   50000, func, key_equality, true);  \
                                                                                        \
        CollectAllStats (&const_size_ht, &csv_data,                                     \
                         "../data/results/[const_size]/[" #func "][stat].csv",          \
                         "../data/results/[const_size]/[" #func "][distribution].csv"); \
        CollectAllStats (&var_size_ht, &csv_data,                                       \
                         "../data/results/[var_size]/[" #func "][stat].csv",            \
                         "../data/results/[var_size]/[" #func "][distribution].csv");   \
                                                                                        \
        HashTableDtor (&const_size_ht);                                                 \
        HashTableDtor (&var_size_ht);                                                   \
    }
  
    #include "test_dsl.h"
    
    TextDtor (&csv_data);

    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second)
{      
    return (strcmp (first, second) == 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

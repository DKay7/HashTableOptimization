#include "hash_functions_to_test.h"
#include "hashtable.h"
#include "utilities.h"
#include "texlib.h"
#include <stdio.h>
#include <locale.h>
#include <assert.h>
#include <time.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    setlocale (LC_ALL, "ru_RU.iso88595");
    setlocale (LC_CTYPE, "ru_RU.iso88595");
    
    Text csv_data = {};
    TextCtor (&csv_data, "data/en-ru.csv");

    #define TEST(func)                                                                              \
    {                                                                                               \
        HashTable<char*, char*> ht = {};                                                            \
        clock_t start, end;                                                                         \
                                                                                                    \
        HashTableCtor<char*, char*> (&ht, 1000,   func, key_equality, true);                        \
                                                                                                    \
        start = clock();                                                                            \
        FillHashTableFromStrCSV (&csv_data, &ht);                                                   \
        end = clock();                                                                              \
        double exec_time = ((double) (end - start)) / CLOCKS_PER_SEC;                               \
                                                                                                    \
        WriteStatsAboutHashTable (&ht, "./data/results/" #func "[various_size][buckets].csv");      \
        WriteExecutionHashTableStats (exec_time, ht.size,                                           \
        "./data/results/" #func "[various_size][stats].csv");                                       \
        HashTableDtor (&ht);                                                                        \
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

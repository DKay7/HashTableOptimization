#include <stdio.h>
#include "utilities.h"
#include "hashtable.h"
#include <time.h>

void FillHashTableFromStrCSV (Text* csv_data, HashTable<char*, char*>* ht)
{   
    char *key, *value;
    char *line;

    for (size_t idx = 0; idx < csv_data->non_empty_lines; idx++)
    {   
        line = csv_data->lines[idx].ptr;
        
        key = strsep(&line, ",");
        value = strsep(&line, ",");

        HashTableInsert<char*, char*>(ht, key, value);
    }

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FreeHashTableAfterFillingFromStrCSV (char** lines_for_free)
{
    while (*(lines_for_free) != NULL)
    {
        free (*lines_for_free);
        lines_for_free++;
    }
}

void WriteStatsAboutHashTable (HashTable<char*, char*>* ht, const char* filename)
{   
    assert (filename);
    assert (ht);

    FILE* stat_file = fopen (filename, "w");
    assert (stat_file);
    
    fprintf (stat_file, "bucket index,bucket size\n");
    
    for (size_t i = 0; i < ht->size; i++)
    {   
        if (ht->buckets[i].status == BUCKET_NOT_EMPTY)
        {   
            fprintf (stat_file, "%lu,%lu\n", i, ht->buckets[i].len);
        }
    }

    fclose (stat_file);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void WriteExecutionHashTableStats (double exec_time, size_t hashtable_size, const char* filename)
{   
    assert (filename);

    FILE* stat_file = fopen (filename, "w");
    fprintf (stat_file, "execution time,table size\n%.5lf,%lu\n", exec_time, hashtable_size);
    fclose (stat_file);

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void CollectAllStats (HashTable<char*, char*>* ht, Text* csv_data, 
                        const char* stat_filename, const char* distribution_stat_filename)
{   
    clock_t start, end; 

    start = clock();                                                                          
    FillHashTableFromStrCSV (csv_data, ht);
    end = clock();                                                                            
    double exec_time = ((double) (end - start)) / CLOCKS_PER_SEC;                             
                                               
    WriteStatsAboutHashTable (ht, distribution_stat_filename);   
    WriteExecutionHashTableStats (exec_time, ht->size, stat_filename); 
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FillIndexesArrayWithRandomValues (int* array, size_t arr_size, int max_index)
{   
    srand (time(0));
     
    for (size_t i = 0; i < arr_size; i++)
        array[i] = rand () % (max_index + 1);
     
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void SearchSpeedTest (int* idx_array, size_t arr_size, HashTable<char *, char*>* ht, Text* csv_data)
{
    for (size_t i = 0; i < arr_size; i++)
    {   
        int index = idx_array[i];
        char* line = csv_data->lines[index].ptr;
        char* key = strsep(&line, ",");

        uint64_t found_idx = HashTableFind<char*, char*> (ht, key);

        if (found_idx >= (uint64_t) ht->values->size + 1)
        {
            fprintf (stderr, "ELEMENT %s NOT FOUND. CONTINUE\n", key);
        }
    }

}

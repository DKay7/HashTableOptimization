#include <stdio.h>
#include "utilities.h"
#include "hashtable.h"

void FillHashTableFromStrCSV (Text* csv_data, HashTable<char*, char*>* ht)
{   
    char *key, *value;
    char *line, *line_for_free;
    // char** lines_for_free = (char**) calloc (csv_data->non_empty_lines + 1, sizeof (*lines_for_free));

    for (size_t idx = 0; idx < csv_data->non_empty_lines; idx++)
    {   
        line = csv_data->lines[idx].ptr;
        
        key = strsep(&line, ",");
        value = strsep(&line, ",");
        // printf ("IDX IS %ld KEY IS %s VALUE IS %s\n", idx, key, value);

        // lines_for_free[idx] = line_for_free;

        HashTableInsert<char*, char*>(ht, key, value);
    }

    // lines_for_free[csv_data->non_empty_lines] = NULL;

    // return lines_for_free;
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

    FILE* stat_file = fopen (filename, "w");
    fprintf (stat_file, "bucket index,bucket size\n");

    for (size_t i = 0; i < ht->size; i++)
    {   
        if (ht->buckets[i].status == BUCKET_NOT_EMPTY)
        {   
            fprintf (stat_file, "%ld,%ld\n", i, ht->buckets[i].len);
        }
    }

    fclose (stat_file);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void WriteExecutionHashTableStats (double exec_time, size_t hashtable_size, const char* filename)
{   
    assert (filename);

    FILE* stat_file = fopen (filename, "w");
    fprintf (stat_file, "execution time,table size\n%.5lf,%ld\n", exec_time, hashtable_size);
    fclose (stat_file);

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

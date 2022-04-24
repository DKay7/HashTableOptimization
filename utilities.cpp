#include <stdio.h>
#include "texlib.h"
#include "utilities.h"
#include "hashtable.h"

void FillHashTableFromStrCSV (HashTable<char*, char*>* ht, const char* path_to_csv)
{   
    Text* csv_data = (Text*) calloc (1, sizeof (*csv_data));
    TextCtor (csv_data, path_to_csv);
    char* key, *value;

    for (size_t idx = 0; idx < csv_data->non_empty_lines; idx++)
    {   
        
        key = strdup (strsep(&csv_data->lines[idx].ptr, ","));
        value = strdup (strsep(&csv_data->lines[idx].ptr, ","));

        HashTableInsert<char*, char*>(ht, key, value);
    }

    TextDtor (csv_data);
    free (csv_data);
}
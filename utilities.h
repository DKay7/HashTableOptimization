#ifndef UTILITIES
#define UTILITIES

#include "hashtable.h"
#include "texlib.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FillHashTableFromStrCSV (Text* csv_data, HashTable<char*, char*>* ht);
void FreeHashTableAfterFillingFromStrCSV (char** lines_for_free);
void WriteStatsAboutHashTable (HashTable<char*, char*>* ht, const char* filename);
void WriteExecutionHashTableStats (double exec_time, size_t hashtable_size, const char* filename);
void CollectAllStats (HashTable<char*, char*>* ht, Text* csv_data, 
                        const char* stat_filename, const char* distribution_stat_filename);
void FillIndexesArrayWithRandomValues (int* array, size_t arr_size, int max_index);
void SearchSpeedTest (int* idx_array, size_t arr_size, HashTable<char *, char*>* ht, Text* csv_data);

#endif
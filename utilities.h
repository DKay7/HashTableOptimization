#ifndef UTILITIES
#define UTILITIES

#include "hashtable.h"
#include "texlib.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void FillHashTableFromStrCSV (Text* csv_data, HashTable<char*, char*>* ht);
void FreeHashTableAfterFillingFromStrCSV (char** lines_for_free);
void WriteStatsAboutHashTable (HashTable<char*, char*>* ht, const char* filename);
void WriteExecutionHashTableStats (double exec_time, size_t hashtable_size, const char* filename);

#endif
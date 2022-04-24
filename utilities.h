#ifndef UTILITIES
#define UTILITIES

#include "hashtable.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char** FillHashTableFromStrCSV (HashTable<char*, char*>* ht, const char* path_to_csv);
void FreeHashTableAfterFillingFromStrCSV (char** lines_for_free);
void WriteStatsAboutHashTable (HashTable<char*, char*>* ht, const char* filename);
void WriteExecutionHashTableStats (double exec_time, size_t hashtable_size, const char* filename);

#endif
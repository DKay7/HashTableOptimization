#include "hashtable.h"
#include "utilities.h"
#include <stdio.h>
#include "default_hash_functions.h"
#include <stdio.h>
#include "utilities.h"
#include "locale.h"




void data_printer (FILE* file, HT_Pair<char*, char*>* data_)
{   
    fprintf (file, "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">"
                   "<tr><td>KEY:</td><td>%s</td></tr>"
                   "<tr><td>VALUE:</td><td>%s </td></tr></table>", 
                   data_->key, data_->value);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool key_equality (char* first, char* second)
{   
    return (strcmp (first, second) == 0);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    setlocale (LC_ALL, "ru_RU.iso88595");
    setlocale (LC_CTYPE, "ru_RU.iso88595");


    HashTable<char*, char*> ht = {};
    HashTableCtor<char*, char*> (&ht, 2, str_hash, key_equality);

    FillHashTableFromStrCSV (&ht, "data/en-ru.csv");
    HashTableDump (&ht, data_printer);
    HashTableDtor (&ht);
    return 0;
}

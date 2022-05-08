#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS

#include <inttypes.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>

#include "hash_functions_to_test.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t const_hash (char* str);
uint64_t first_letter_code_hash (char* str);
uint64_t len_hash (char* str);
uint64_t sum_of_letter_codes_hash (char* str);
uint64_t rol_hash (char* str);
uint64_t ror_hash (char* str);
uint64_t polynimial_rolling_hash (char* str);
uint64_t murmur_hash(char* string);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#endif
#include <inttypes.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>

#include "hash_functions_to_test.h"

uint64_t const_hash (char* str)
{   
    (void ) str;
    return 1ul;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t first_letter_code_hash (char* str)
{   
    assert (str);
    return (uint64_t)str[0];
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t len_hash (char* str)
{   
    assert (str);
    return strlen (str);
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t sum_of_letter_codes_hash (char* str)
{
    assert (str);

    uint64_t hash = 0;

    while (*str++ != 0)
    {
        hash += (uint64_t) (*str);
    }

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t rol_hash (char* str)
{   
    assert (str);

    const int shift_size_bits = CHAR_BIT * sizeof (uint64_t) - 1;
    const uint64_t highest_bit_mask = (uint64_t)1 << shift_size_bits;

    uint64_t hash = (uint64_t)str[0];
    
    while (*(str++) != 0)
    {
        hash = ((hash << 1) + ((hash & highest_bit_mask) >> shift_size_bits)) ^ (uint64_t)(*str);
    }

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t ror_hash (char* str)
{
    assert (str);

    const int shift_size_bits = CHAR_BIT * sizeof (uint64_t) - 1;
    const int lowest_bit_mask = 1;

    uint64_t hash = (uint64_t)str[0];

    while (*(str++) != 0)
    {
        hash = ((hash >> 1) + ((hash & lowest_bit_mask) << shift_size_bits)) ^ (uint64_t)(*str);
    }

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

uint64_t polynimial_rolling_hash (char* str)
{
    assert (str);
    const int m = 1e9 + 9;
    const int p = 53;

    uint64_t hash = 0;
    uint64_t power = 1;

    while (*(str++) != 0)
    {
        hash = (hash + (uint64_t)((*str) - 'a' + 1) * power) % m;
        power = (p * power) % m;
    }

    return hash;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

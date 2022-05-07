# Исследование и оптимизация хэш-таблицы
Данное задание посвящено написанию, исследованию работы и оптимизации структуры данных хэш таблица.

## Некоторые детали реализации
В первую очередь, хотелось бы отметить некоторые отличительные черты данной хэш-таблицы.
1. Коллизии разрешаются методом цепочек
2. Сама таблица умеет расширяться, когда коэффициент заполнения (количество элементов, на одну ячейку хэш-таблицы) превышает 1.5
3. Хэш-таблица является "кэш-френдли", то есть реализация подразумевает уменьшение кэш-мисов. Достигнуто это следующим образом:
    1. Во-первых, связный список, используемый для разрешения коллизий представляет из себя массив, то есть хранится в памяти последовательно, что увеличивает вероятность того, что все элементы списка окажутся в кэше
    2. Во-вторых, метод цепочек немного видоизменен. Стандратная реализация предполагает, что каждый элемент хэш-таблицы имеет свой связный список, в который кладутся элементы при возникновении коллизий. В данном же проекте, связный список -- один, а каждый элемент хранит начало подсписка и длину. Такое решение также должно уменьшать количество кэшмисов, потому что и сама таблица, и связный список -- массивы, хранящиеся в памяти последовательно. В дальнейшем, один элемент хэш-таблицы (то есть подсписок и его длину) мы будем называть бакетом (от англ. bucket -- ведро).

## Данные
Теперь пару слов о данных, на которых производились тесты. Для объективности тестирования, данных должно быть много, поэтому было принято решение взять англо-русский словарь на 64000 слов и выражений. После удаления дубликатов, пустых значений (без перевода), и слишком длинных строк, в словаре осталось около 55000 строк формата "английское выражение -- перевод". Ключом хэштаблицы являлась фраза на английском, а значением -- перевод.

## Тестирование
В первую очередь, необходимо выбрать наилучшую хэш-функцию, дающую минимум коллизий. Для тестирования были предложены следующие функции:

1. `const_hash`:
```C++
uint64_t const_hash (char* str)
{   
    (void ) str;
    return 1ul;
}
```

2. `first_letter_code_hash`:
```C++
uint64_t first_letter_code_hash (char* str)
{   
    assert (str);
    return (uint64_t)str[0];
}
```C++

3. `len_hash`:
```C++
uint64_t len_hash (char* str)
{   
    assert (str);
    return strlen (str);
}
```

4. `sum_of_letter_codes_hash`:
```C++
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
```

5. `rol_hash`:
```C++
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
```

6. `ror_hash`:
```C++
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
```

7. `polynimial_rolling_hash`:
```C++
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
```

Тестирование произоводилось следующим образом:
1. Создавалось два объекта хэш-таблицы, с начальным размером в 50000 элементов. Одна хэштаблица могла расширяться, вторая -- нет.
2. В хэш-таблицу вставлялись элементы из словаря по описанному выше принципу.
3. Производился замер времени вставки, вычислялась дисперсия распределения длин подсписков (напомню, что каждый эелмент хэш-таблицы предствляет из себя подсписок, это необходимо для разрешения коллизий).

По результатам работы были составлены следующие таблицы:

Для хэш-таблицы постоянного размера:
| **Имя хэш\-функции**             | **Дисперсия** | **Время, секунды** | **Размер таблицы** |
|----------------------------------|---------------|--------------------|--------------------|
| **const\_hash**                  | nan           | 19\.28271          | 50000              |
| **first\_letter\_code\_hash**    | 3384202\.89   | 1\.15411           | 50000              |
| **len\_hash**                    | 4418417\.99   | 2\.86783           | 50000              |
| **sum\_of\_letter\_codes\_hash** | 1049\.22      | 0\.07684           | 50000              |
| **ror\_hash**                    | 16\.776       |  0\.02411          | 50000              |
| **rol\_hash**                    | 5\.044        | 0\.01937           | 50000              |
| **polynimial\_rolling\_hash**    | 1\.136        | 0\.02191           | 50000              |


Для расширяющейся хэш-таблицы:
| **Имя хэш\-функции**             | **Дисперсия** | **Время, секунды** | **Начальный размер таблицы** | **Конечный размер таблицы** |
|----------------------------------|---------------|--------------------|------------------------------|-----------------------------|
| **const\_hash**                  | nan           | 23\.9094           | 50000                        | 100000                      |
| **first\_letter\_code\_hash**    | 3384202\.89   | 1\.76362           | 50000                        | 100000                      |
| **len\_hash**                    | 4418417\.99   | 2\.92111           | 50000                        | 100000                      |
| **sum\_of\_letter\_codes\_hash** | 1049\.22      | 0\.08114           | 50000                        | 100000                      |
| **ror\_hash**                    | 16\.77        | 0\.03716           | 50000                        | 100000                      |
| **rol\_hash**                    | 3\.54         | 0\.03268           | 50000                        | 100000                      |
| **polynimial\_rolling\_hash**    | 0\.661        | 0\.03734           | 50000                        | 100000                      |

Из таблиц можно сделать следующие выводы:
1. Никогда не используйте `cons_hash`, это бессмысленно.

2. Наилучшими оказались `rol_hash`, `ror_hash` и `polynimial_rolling_hash`.

3. По верхним строчкам таблицы может показаться, что добавление функции расширения, не дает ничего, кроме увелечения времени работы (при расширении нужно пересчитать хэш всех элементов), тем не менее, по нижним строчкам видно, что засчет расширения таблицы время вставки уменьшилось настолько сильно, что общее время работы либо уменьшилось, либо почти не изменилось. Это говорит о том, что функция расширения таблицы, в совокупности с хорошей хэш-функцией уменьшает время вставки.

4. Как и со временем работы, если посмотреть на верхние строчки таблицы, можно подумать, что увеличение размера таблицы никак не повлияло на дисперсию размеров бакетов, но вызвано это было плохой хэш-функцией. Если же посмотреть на нижние строчки таблицы, в которых предствлены относительно хорошие хэш-функции, можно понять, что увеличение размера таблицы на порядок уменьшило дисперсию.

Таким образом, были приняты следующие решения:
1. Использовать `polynimial_rolling_hash` в качестве хэш-функции.
2. Оставить хэш-таблицу расширяемой.


# Оптимизация
Теперь, когда мы выяснили, какие параметры таблицы использовать лучше всего, перейдем к оптимизации.

Первым делом отметим каким образом мы тестировали хэш-таблицу на производительность. Для этого приведем код функции `main` исполняемой программы.

```cpp
int main()
{
    Text csv_data = {};
    TextCtor (&csv_data, "../data/en-ru.csv");
    const size_t idx_arr_size = 256;
    int* idx_for_search_array = (int*) calloc (idx_arr_size, sizeof(*idx_for_search_array));

    HashTable<char*, char*> ht = {};
    HashTableCtor<char*, char*> (&ht, 50000, polynimial_rolling_hash, key_equality);

    FillIndexesArrayWithRandomValues (idx_for_search_array, idx_arr_size, csv_data.non_empty_lines);

    FillHashTableFromStrCSV (&csv_data, &ht);

    SearchSpeedTest (idx_for_search_array, idx_arr_size, &ht, &csv_data);

}
```

Как видно из приведенного выше кода, если не вдаваться в детали реализации, мы создавали массив из 256 ключей, который заполняли случайными ключами из словаря, после этого мы искали все 256 ключей в хэш-таблице.

Профилирование производилось при помощи утилиты `perf`. Для сбора статистики запускалась следующая команда.

```sudo perf record -e cpu-clock,cache-misses,branch-misses --freq=10000 ./main```

Первый тест, без оптимизаций (в дальнейшем мы будем сравнивать результаты оптимизаций с ним) дал следующие показатели:

<details>
<summary>Результат первого теста</summary>
<pre>
# Samples: 469  of event 'cpu-clock'
# Event count (approx.): 46900000  
#  
# Overhead  Command  Symbol                                     
# ........  .......  ..........................................  
#  
    23.24%  main     [.] polynimial_rolling_hash  
     8.96%  main     [.] __HashTableSearchForKey<char*, char*>  
     7.89%  main     [.] LLIncreaseSize<HT_Pair<char*, char*> >
     4.05%  main     [.] __HashTableGetPosition<char*, char*>
     1.71%  main     [.] HashTableInsert<char*, char*>
     1.28%  main     [.] FillHashTableFromStrCSV
     1.07%  main     [.] FillLinesArray
     1.07%  main     [.] LLInsertAfter<HT_Pair<char*, char*> >
     0.64%  main     [.] HashTableBucketsArrayCtor
     0.64%  main     [.] LLCtor<HT_Pair<char*, char*> >
     0.43%  main     [.] CountSymbol
     0.43%  main     [.] PoisonData<HT_Pair<char*, char*> >
     0.21%  main     [.] HashTableFind<char*, char*>
     0.21%  main     [.] key_equality
     0.21%  main     [.] 0x0000000000001244
     0.21%  main     [.] 0x0000000000001260


# Samples: 397  of event 'cache-misses'
# Event count (approx.): 840712
#
# Overhead  Command  Symbol                                    
# ........  .......  ..........................................
#
    20.02%  main     [.] polynimial_rolling_hash
     8.64%  main     [.] LLIncreaseSize<HT_Pair<char*, char*> >
     5.04%  main     [.] __HashTableSearchForKey<char*, char*>
     2.15%  main     [.] HashTableInsert<char*, char*>
     1.89%  main     [.] __HashTableGetPosition<char*, char*>
     1.64%  main     [.] FillLinesArray
     0.44%  main     [.] FillHashTableFromStrCSV
     0.35%  main     [.] key_equality
     0.26%  main     [.] HashTableBucketsArrayCtor
     0.19%  main     [.] 0x0000000000001290
     0.10%  main     [.] LLInsertAfter<HT_Pair<char*, char*> >


# Samples: 359  of event 'branch-misses'
# Event count (approx.): 332997
#
# Overhead  Command  Symbol                                   
# ........  .......  .........................................
#
    26.19%  main     [.] __HashTableGetPosition<char*, char*>
     5.83%  main     [.] __HashTableSearchForKey<char*, char*>
     5.80%  main     [.] HashTableInsert<char*, char*>
     5.33%  main     [.] polynimial_rolling_hash
     0.80%  main     [.] FillLinesArray
     0.53%  main     [.] FillHashTableFromStrCSV
     0.43%  main     [.] CountSymbol
     0.24%  main     [.] HashTablePairCtor<char*, char*>
     0.22%  main     [.] key_equality
     0.22%  main     [.] HashTableFind<char*, char*>
</pre>
</details>

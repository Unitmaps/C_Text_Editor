#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include"mystring.h"

void* safe_malloc(uint32_t size)
{
    void* temp = malloc(size);
    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

void* safe_calloc(uint32_t amount, uint32_t size)
{
    void* temp = calloc(amount, size);
    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

void* safe_realloc(void* ptr, uint32_t size)
{
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL)
    {
        fprintf(stderr, "Memory reallocation error");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

Strng* s_create_strng(uint32_t initial_capacity)
{
    Strng* strng = safe_malloc(sizeof(Strng));
    strng->str = safe_malloc(sizeof(char) * initial_capacity);
    strng->str[0] = '\0';
    strng->size = 1;
    strng->capacity = initial_capacity;
    return strng;
}

void s_clean_strng(Strng* strng)
{
    free(strng->str);
}

void s_destroy_strng(Strng* strng)
{
    free(strng->str);
    strng->str = NULL;
    strng->size = 0;
    free(strng);
}

static void s_increase_strng(Strng* strng)
{
    if (strng->capacity > 1048576)
    {
        strng->capacity += 1048576;
    }
    else
    {
        strng->capacity *= 2;
    }
    strng->str = safe_realloc(strng->str, sizeof(char) * strng->capacity);
}

void s_add_char(Strng* strng, char value)
{
    if (strng->size + 1 > strng->capacity)
    {
        s_increase_strng(strng);
    }
    strng->str[strng->size - 1] = value;
    strng->str[strng->size] = '\0';
    strng->size++;
}

void s_add_string(Strng* strng, char* text, uint32_t text_len)
{
    while (strng->size + text_len > strng->capacity)
    {
        s_increase_strng(strng);
    }
    for (uint16_t i = 0; i < text_len; i++)
    {
        strng->str[strng->size - 1 + i] = text[i];
    }
    strng->str[strng->size - 1 + text_len] = '\0';
    strng->size += text_len;
}

void s_insert_char(Strng* strng, uint32_t index, char value)
{
    if (strng->size + 1 > strng->capacity)
    {
        s_increase_strng(strng);
    }
    uint32_t elems_to_move = strng->size - index;
    memmove(strng->str + index + 1, strng->str + index, sizeof(char) * elems_to_move);
    strng->str[index] = value;
    strng->size++;
}

void s_insert_string(Strng* strng, uint32_t index, char* text, uint32_t text_len)
{
    while (strng->size + text_len > strng->capacity)
    {
        s_increase_strng(strng);
    }
    uint32_t elems_to_move = strng->size - index;
    memmove(strng->str + index + text_len, strng->str + index, sizeof(char) * elems_to_move);
    for (uint16_t i = 0; i < text_len; i++)
    {
        strng->str[index + i] = text[i];
    }
    strng->size += text_len;
}
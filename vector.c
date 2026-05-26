#define __USE_MINGW_ANSI_STDIO 1
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include"vector.h"
#include"mystring.h"

Vector* create(uint32_t initial_capacity)
{
    Vector* vector = safe_malloc(sizeof(Vector));
    vector->data = safe_malloc(sizeof(Strng*) * initial_capacity);
    vector->size = 0;
    vector->capacity = initial_capacity;
    return vector;
}

void clean_vector(Vector* vector)
{
    for (uint32_t i = 0; i < vector->size; i++)
    {
        s_destroy_strng(vector->data[i]);
        vector->data[i] = NULL;
    }
    vector->size = 0;
}

void destroy_vector(Vector* vector)
{
    for (uint32_t i = 0; i < vector->size; i++)
    {
        s_destroy_strng(vector->data[i]);
        vector->data[i] = NULL;
    }
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    free(vector);
}

static void increase_vector(Vector* vector)
{
    if (vector->capacity > 1048576)
    {
        vector->capacity += 1048576;
    }
    else
    {
        vector->capacity *= 2;
    }
    vector->data = safe_realloc(vector->data, sizeof(Strng*) * vector->capacity);
}

void add_back(Vector* vector, char* value, uint32_t len)
{
    if (vector->size + 1 > vector->capacity)
    {
        increase_vector(vector);
    }
    Strng* strng = s_create_strng(1024);
    s_add_string(strng, value, len);
    vector->data[vector->size] = strng;
    vector->size++;
}

void add_new_string(Vector* vector, uint32_t initial_capacity)
{
    if (vector->size + 1 > vector->capacity)
    {
        increase_vector(vector);
    }
    Strng* strng = s_create_strng(initial_capacity);
    vector->data[vector->size] = strng;
    vector->size++;
}

/*void insert(Vector* vector, uint32_t index, char* value)
{
    if (vector->size + 1 > vector->capacity)
    {
        increase(vector);
    }
    uint32_t elems_to_move = vector->size - index;
    memmove(vector->data + index + 1, vector->data + index, sizeof(Strng*) * elems_to_move);
    vector->data[index] = value;
    vector->size++;
}*/
#define __USE_MINGW_ANSI_STDIO 1
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vector.h"
int main() {
    return 0;
}

void* safe_malloc(size_t size)
{
    void* temp = malloc(size);
    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

void* safe_calloc(size_t amount, size_t size)
{
    void* temp = calloc(amount, size);
    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

void* safe_realloc(void* ptr, size_t size)
{
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL)
    {
        fprintf(stderr, "Memory reallocation error");
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

Vector* create()
{
    Vector* vector = safe_malloc(sizeof(Vector));
    return vector;
}

void init(Vector* vector, size_t initial_capacity)
{
    vector->data = safe_malloc(sizeof(char**) * initial_capacity);
    vector->size = 0;
    vector->capacity = initial_capacity;
}

void destroy(Vector* vector)
{
    for (size_t i = 0; i < vector->size; i++)
    {
        free(vector->data[i]);
        vector->data[i] = NULL;
    }
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    free(vector);
}

static void increase(Vector* vector)
{
    if (vector->capacity > 1048576)
    {
        vector->capacity += 1048576;
    }
    else
    {
        vector->capacity *= 2;
    }
    vector->data = safe_realloc(vector->data, sizeof(char*) * vector->capacity);
}

void add_back(Vector* vector, char* value)
{
    if (vector->size + 1 > vector->capacity)
    {
        increase(vector);
    }
    vector->data[vector->size] = value;
    vector->size++;
}

char* pop_back(Vector* vector)
{
    char* value = vector->data[vector->size - 1];
    vector->size--;
    return value;
}

void insert(Vector* vector, size_t index, char* value)
{
    if (vector->size + 1 > vector->capacity)
    {
        increase(vector);
    }
    size_t elems_to_move = vector->size - index;
    memmove(vector->data + index + 1, vector->data + index, sizeof(char*) * elems_to_move);
    vector->data[index] = value;
    vector->size++;
}

void erase(Vector* vector, size_t index)
{
    size_t elems_to_move = vector->size - 1 - index;
    memmove(vector->data + index, vector->data + index + 1, sizeof(char*) * elems_to_move);
    vector->size--;
}
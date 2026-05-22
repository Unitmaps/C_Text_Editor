#ifndef Vector_H
#define Vector_H
#include<stddef.h>

typedef struct
{
    char** data;
    size_t size;
    size_t capacity;
} Vector;

void* safe_malloc(size_t size);
void* safe_calloc(size_t amout, size_t size);
void* safe_realloc(void* ptr, size_t size);

Vector* create();
void init(Vector* vector, size_t initial_capacity);
void destroy(Vector* vector);

void add_back(Vector* vector, char* value);
char* pop_back(Vector* vector);
void insert(Vector* vector, size_t index, char* value);
void erase(Vector* vector, size_t index);

#endif
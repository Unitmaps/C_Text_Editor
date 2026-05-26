#ifndef Vector_H
#define Vector_H
#include<stdint.h>
#include"mystring.h"

typedef struct
{
    Strng** data;
    uint32_t size;
    uint32_t capacity;
} Vector;

Vector* create(uint32_t initial_capacity);
void destroy_vector(Vector* vector);
void clean_vector(Vector* vector);

void add_back(Vector* vector, char* value, uint32_t len);
void add_new_string(Vector* vector, uint32_t initial_capacity);
//void insert(Vector* vector, uint32_t index, char* value);

#endif
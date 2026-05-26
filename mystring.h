#ifndef MyString_H
#define MyString_H
#include<stdint.h>

typedef struct 
{
    char* str;
    uint32_t size;
    uint32_t capacity;
} Strng;

void* safe_malloc(uint32_t size);
void* safe_calloc(uint32_t amout, uint32_t size);
void* safe_realloc(void* ptr, uint32_t size);

Strng* s_create_strng(uint32_t initial_capacity);
void s_clean_strng(Strng* strng);
void s_destroy_strng(Strng* strng);
void s_add_char(Strng* strng, char value);
void s_add_string(Strng* strng, char* text, uint32_t text_len);
void s_insert_char(Strng* strng, uint32_t index, char value);
void s_insert_string(Strng* strng, uint32_t index, char* text, uint32_t text_len);

#endif
#ifndef Logic_H
#define Logic_H
#define MAX_CHAR_PER_VECTOR 1024
#define BASIC_CHAR_PER_VECTOR 768
#include"vector.h"
#include"stdint.h"

void append(Vector* buff);
void new_line(Vector* buff);
void save(char* filename, Vector* buff);
void load(char* filename, Vector* buff);
void print(Vector* buff);
void insert_buff(Vector* buff, uint32_t index, Strng* text);
void search(Vector* buff, Strng* substring);
void clean_buff(Vector* buff);
void programm_exit(Vector* buff);

#endif
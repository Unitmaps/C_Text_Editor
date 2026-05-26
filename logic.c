#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include"vector.h"
#include"logic.h"
#include"mystring.h"

uint8_t is_file_exist(char* filename);

void append(Vector* buff)
{
    if (buff->data[buff->size - 1]->size >= buff->data[buff->size - 1]->capacity - 512)
    {
        add_new_string(buff, 1024);
    }
    int16_t c;
    for (uint16_t i = 0; (c = getchar()) != '\n'; i++)
    {
        s_add_char(buff->data[buff->size - 1], c);
    }
}

void new_line(Vector* buff)
{
    s_add_char(buff->data[buff->size - 1], '\n');
}

void save(char* filename, Vector* buff)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "File editing error\n");
        exit(EXIT_FAILURE);
    }
    for (uint16_t i = 0; i < buff->size; i++)
    {
        fputs(buff->data[i]->str, file);
    }
    fclose(file);
    return;
}

void load(char* filename, Vector* buff)
{
    if (!is_file_exist(filename))
    {
        printf("File doesn't exists\n");
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File opening error\n");
        exit(EXIT_FAILURE);
    }
    int16_t c;
    clean_vector(buff);
    add_new_string(buff, 1024);
    for (uint16_t i = 0; (c = fgetc(file)) != EOF; i++)
    {
        if (c == '\n')
        {
            add_new_string(buff, 1024);
        }
        s_add_char(buff->data[buff->size - 1], c);
    }
    fclose(file);
}

void print(Vector* buff)
{
    for (uint16_t i = 0; i < buff->size; i++)
    {
        printf("%s", buff->data[i]->str);
    }
    printf("\n");
}

void insert_buff(Vector* buff, uint32_t index, Strng* strng)
{
    uint32_t counter = 0;
    for (uint16_t i = 0; i < buff->size; i++)
    {
        if (counter + strlen(buff->data[i]->str) > index)
        {
            uint32_t cur_index = index - counter - 1;
            s_insert_string(buff->data[i], cur_index, strng->str, strng->size - 1);
            break;

        }
        counter += strlen(buff->data[i]->str);
    }
    if (counter < index)
    {
        printf("Index out of range error\n");
        exit(EXIT_FAILURE);
    }
}

void search(Vector* buff, Strng* substring)
{
    uint16_t num_results = 0;
    uint16_t results_capacity = 8;
    uint32_t* results = safe_malloc(sizeof(uint32_t) * results_capacity);
    uint32_t cur_index = 0;
    char* match;
    for (uint32_t i = 0; i < buff->size; i++)
    {
        while ((match = strstr(buff->data[i]->str + cur_index, substring->str)) != NULL)
        {
            if (num_results + 1 >= results_capacity)
            {
                results_capacity *= 2;
                results = safe_realloc(results, results_capacity);
            }
            results[num_results] = (match - buff->data[i]->str) / sizeof(char);
            num_results++;
            cur_index += (match - buff->data[i]->str) / sizeof(char) + strlen(substring->str);
        }
    }
    if (num_results == 0)
    {
        printf("No matches\n");
    }
    else
    {
        printf("Found matches at index:\n");
        for (uint16_t i = 0; i < num_results; i++)
        {
            printf("%d\n", results[i]);
        }
    }
    free(results);
    free(match);
}

void clean_buff(Vector* buff)
{
    clean_vector(buff);
    add_new_string(buff, 1024);
}

void programm_exit(Vector* buff)
{
    destroy_vector(buff);
}

uint8_t is_file_exist(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }
    else
    {
        fclose(file);
        return 1;
    }
}
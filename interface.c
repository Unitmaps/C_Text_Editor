#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include"vector.h"
#include"interface.h"
#include"logic.h"
#include"mystring.h"

void interface();
void clean_sys_buff();
void clean_screen();
void show_help();

void interface()
{
    Vector* buff = create(64);
    add_new_string(buff, 1024);
    uint8_t exit = 0;
    while (!exit)
    {
        int option;
        printf("Choose command:\n");
        scanf("%d", &option);
        clean_sys_buff();
        switch (option)
        {
            case APPEND:
            {
                clean_screen();
                printf("Print text: ");
                append(buff);
                clean_screen();
                break;
            }
            case NEW_LINE:
            {
                clean_screen();
                new_line(buff);
                break;
            }
            case SAVE:
            {
                clean_screen();
                char* filename = safe_malloc(sizeof(char) * 60);
                printf("Enter file name:\n");
                scanf("%s", filename);
                clean_sys_buff();
                save(filename, buff);
                free(filename);
                clean_screen();
                break;
            }
            case LOAD:
            {
                clean_screen();
                char* filename = safe_malloc(sizeof(char) * 60);
                printf("Enter file name:\n");
                scanf("%s", filename);
                clean_sys_buff();
                load(filename, buff);
                free(filename);
                clean_screen();
                break;
            }
            case PRINT:
            {
                clean_screen();
                print(buff);
                break;
            }
            case INSERT:
            {
                clean_screen();
                uint32_t index;
                scanf("%d", &index);
                clean_sys_buff();
                Strng* strng = s_create_strng(1024);
                char c;
                for (uint16_t i = 0; (c = getchar()) != '\n'; i++)
                {
                    s_add_char(strng, c);
                }
                insert_buff(buff, index, strng);
                break;
            }
            case SEARCH:
            {
                clean_screen();
                clean_sys_buff();
                Strng* strng = s_create_strng(1024);
                char c;
                for (uint16_t i = 0; (c = getchar()) != '\n'; i++)
                {
                    s_add_char(strng, c);
                }
                search(buff, strng);
                break;
            }
            case CLEAN:
            {
                clean_screen();
                clean_buff(buff);
                break;
            }
            case EXIT:
            {
                clean_screen();
                programm_exit(buff);
                exit = 1;
                break;
            }
            default:
            {
                clean_screen();
                show_help();
            }
        }
    }
}

void clean_sys_buff()
{
    int16_t c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clean_screen()
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void show_help()
{
    printf("Unknown command. All available commands are below:\n\n");
    printf("====== Commands list ======\n");
    printf("1 - Append text to the end\n");
    printf("2 - Start new line\n");
    printf("3 - Save text\n");
    printf("4 - Load text\n");
    printf("5 - Print text from buffer\n");
    printf("6 - Insert text\n");
    printf("7 - Search\n");
    printf("8 - Clear buffer\n");
    printf("9 - Exit\n\n");
}
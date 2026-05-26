#ifndef Interface_H
#define Interface_H

typedef enum
{
    APPEND = 1,
    NEW_LINE,
    SAVE,
    LOAD,
    PRINT,
    INSERT,
    SEARCH,
    CLEAN,
    EXIT
} Comnds;

void interface();

#endif
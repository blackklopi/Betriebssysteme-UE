#include "helpers.h"
#include <stdio.h>

//1. Copy all characters until current character == ' " '
//2.1 set in_quotes if i + 1 != ' " '
// 2.1.2 if i + 1 == ' " ' copy and skip i + 1 iteration
// 2.1.3 if i + 2 == ' " ' and i + 3 != ' " ' ==> unset in_quotes (exit quotes mode)
// 2.1.4 if i + 3 == ' " ' skip i + 3 iteration

// 2.2 skip i + 1 iteration if i + 1 == ' " ' and copy one ' " '
// 2.2.1 if i + 2 == ' " ' go to 2.1.2
void initQuotesMode(char inputBuffer[], char outputBuffer[])
{
    int in_quotes = 0;
    int fieldPos = 0;

    for (int i = 0; inputBuffer[i] != '\0'; i++)
    {
        if (inputBuffer[i] == '"')
        {
            if (in_quotes && inputBuffer[i + 1] == '"')
            {
                outputBuffer[fieldPos++] = '"';
                i++;
            }
            else
            {
                in_quotes = !in_quotes;
            }
        }
        else if (inputBuffer[i] == ',' && !in_quotes)
        {
            outputBuffer[fieldPos] = '\0';
            printf("Feld: %s\n", outputBuffer);
            fieldPos = 0;
        }
        else
        {
            outputBuffer[fieldPos++] = inputBuffer[i];
        }
    }
    outputBuffer[fieldPos] = '\0';
}

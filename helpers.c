#include "helpers.h"

#include <stdbool.h>
#include <stdio.h>

// Config config = {
//     .fieldcounter = 0,
//     .inDelimiter = ',',
//     .outDelimiter = ',',
//     .besteFunktion = 0,
//     .header = 0,
//     .ignoreLines = 0,
//     .strict = 0,
//     .file = NULL
// };

//Copy all characters until current character == ' " '
//delete all single quotes ("...") and put fake inDelimiter into buffer
//replace double quote with single quote
//if outside quotes replace every inDelimiter with outDelimiter
void initQuotesMode(char inputBuffer[], char outputBuffer[], Config* conf)
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
        else if (!in_quotes && inputBuffer[i] == conf->inDelimiter)
        {
            outputBuffer[fieldPos++] = conf->outDelimiter;
        }
        else if (in_quotes && inputBuffer[i] == conf->inDelimiter)
        {
            outputBuffer[fieldPos++] = inputBuffer[i];
        }
        else
        {
            outputBuffer[fieldPos++] = inputBuffer[i];
        }
    }
    outputBuffer[fieldPos] = '\0';
}

void processFields(char outputBuffer[], Config* conf)
{
    int curFieldStart = 0;
    int curFieldEnd = 0;
    int fieldInd = 0;
    int currentColumn = 1;
    bool outsideDelim = false;

    int i = 0;
    while (outputBuffer[i] != '\0' && fieldInd != conf->fieldcounter)
    {
        curFieldStart = i;

        // traverse buffer until delimiter or end of line
        while (outputBuffer[i] != '\0' && outputBuffer[i] != conf->outDelimiter)
        {
            i++;
        }

        curFieldEnd = i;

        if (conf->fields[fieldInd] == currentColumn)
        {
            fieldInd++;
            // ignore all inDelimiters that occur before a field
            // if the field itself contains a inDelimiter, print it
            if (outsideDelim)
            {
                // once a column is valid, outsideDelim = true and the outDelimiter will be appended to the previous field
                fprintf(stdout, "%c", conf->outDelimiter);
            }

            for (int j = curFieldStart; j < curFieldEnd; j++)
            {
                fprintf(stdout, "%c", outputBuffer[j]);
            }
            outsideDelim = true;
        }

        if (outputBuffer[i] == conf->outDelimiter)
        {
            i++;
        }
        currentColumn++;
    }
}

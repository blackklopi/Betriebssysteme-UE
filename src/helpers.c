#include "../util/helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void initWithoutQuotesMode(char inputBuffer[], char outputBuffer[], Config* conf)
{
    // use internal delimiter so that if inDelimiter=outDelimiter still works
    //0x1F = ASCII Unit Seperator that never appears in a file
    //provided by chat-gpt
    char TEMP_DELIM = 0x1F;

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
            outputBuffer[fieldPos++] = TEMP_DELIM;
        }
        else if (in_quotes && inputBuffer[i] == conf->inDelimiter)
        {
            outputBuffer[fieldPos++] = TEMP_DELIM;
        }
        else
        {
            outputBuffer[fieldPos++] = inputBuffer[i];
        }
    }
    outputBuffer[fieldPos] = '\0';
}
void initQuotesMode(char inputBuffer[], char outputBuffer[], Config* conf)
{
    // use internal delimiter so that if inDelimiter=outDelimiter still works
    //0x1F = ASCII Unit Seperator that never appears in a file
    //provided by chat-gpt
    char TEMP_DELIM = 0x1F;

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
            outputBuffer[fieldPos++] = TEMP_DELIM;
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
    // use internal delimiter so that if inDelimiter=outDelimiter still works
    //0x1F = ASCII Unit Seperator that never appears in a file
    //provided by chat-gpt
    char TEMP_DELIM = 0x1F;

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
        while (outputBuffer[i] != '\0' && outputBuffer[i] != TEMP_DELIM)
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

        if (outputBuffer[i] == TEMP_DELIM)
        {
            i++;
        }
        currentColumn++;
    }
}

int handleInput(FILE* input, Config* config)
{
    //todo

    char inputBuffer[1024];
    char outputBuffer[1024];
    int lineNum = 0;

    while (fgets(inputBuffer, sizeof(inputBuffer), input))
    {
        // extract \n for further processing, add it back at the end of processing and line end
        if (inputBuffer[strlen(inputBuffer) - 1] == '\n')
        {
            inputBuffer[strlen(inputBuffer) - 1] = '\0';
        }

        //header handling
        if (lineNum == 0 && config->header)
        {
            // if header is set it will never be skipped by -s
        }else if (lineNum == 0 && !config->header) {
            lineNum++;
            continue;
        }
        //-s skip lines that do not have the right delimiter
        else if (config->ignoreLines && strchr(inputBuffer, config->inDelimiter) == NULL)
        {
            continue;
        }

        // initialize unitialized outputBuffer, gets skipped by -s check for small performance gain
        strcpy(outputBuffer, inputBuffer);

        // -q,
        if (config->besteFunktion)
        {
            initQuotesMode(inputBuffer, outputBuffer, config);
        }else {
            //todo
            //without quote
            initWithoutQuotesMode(inputBuffer, outputBuffer, config);
        }

        // process fields
        processFields(outputBuffer, config);

        // char * result = handleLine(line);
        // printLine(result);

        //free all strings
        //return 0 and err msgs

        lineNum++;
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "linenum: %d\n", lineNum);
    fprintf(stdout, "fieldcounter: %d\n", config->fieldcounter);
    fprintf(stdout, "field: %d\n", config->fields[0]);

    return 1;

    //zeilenweise lesen

    //zeile splitten

    //print lines
}
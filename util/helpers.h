#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXFIELDS 20

typedef struct Config
{
    int fields[MAXFIELDS];
    int fieldcounter;
    char inDelimiter;
    char outDelimiter;
    int besteFunktion;
    int header;
    int ignoreLines;
    int strict;
    char* file;
} Config;

void initQuotesMode(char inputBuffer[], char outputBuffer[], Config* conf);

void processFields(char outputBuffer[], Config* conf);

int handleInput(FILE* input, Config* config);

void initWithoutQuotesMode(char inputBuffer[], char outputBuffer[], Config* conf);


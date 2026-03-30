#include "ccut.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFIELDS 20

typedef struct Config
{
    int* fields[MAXFIELDS];
    int fieldcounter;
    char inDelimiter;
    char outDelimiter;
    int besteFunktion;
    int header;
    int ignoreLines;
    int strict;
    char* file;
} Config;

void help(char* progName);

int handleArguments(int argc, char* argv[], Config* config);

void version(void);

int getFields(char* str_fields, Config* config);

int handleInput(FILE* file, Config* config);

int main(int argc, char* argv[])
{
    printf("%d\n", argc);

    //default config
    Config config = {
        .fieldcounter = 0,
        .inDelimiter = ',',
        .outDelimiter = ',',
        .besteFunktion = 0,
        .header = 0,
        .ignoreLines = 0,
        .strict = 0,
        .file = NULL
    };

    if (!handleArguments(argc, argv, &config))
    {
        //Fehler
        return 1;
    }

    //hier wenn kein fehler bei argumente
    FILE* input;
    int close = 0;

    if (config.file == NULL)
    {
        input = stdin;
    }
    else
    {
        input = fopen(config.file, "r");
        close = 1;
        if (input == NULL)
        {
            fprintf(stderr, "File konnte nicht gelsen werden\n");
            return 0;
        }
    }

    int res = handleInput(input, &config);
    //todo

    if (close)
    {
        fclose(input);
    }
    return 1;
}

int handleInput(FILE* input, Config* config)
{
    //todo
}

int handleArguments(int argc, char* argv[], Config* config)
{
    int fieldsInput = 0;

    //starte bei 1 weil programmname 0
    for (int i = 1; i < argc; i++)
    {
        char* arg = argv[i];

        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
        {
            help(arg);

            //Abbruch bei help
            return 0;
        }
        else if (strcmp(arg, "--version") == 0)
        {
            version();

            //Abbruch bei version
            return 0;
        }
        else if (strcmp(arg, "-f") == 0)
        {
            int fields = i + 1;
            if (fields >= argc)
            {
                fprintf(stderr, "Bei Verwendung von -f müssen Spalten angegeben werden.\n");
                return 1;
            }
            if (!getFields(argv[fields], config))
            {
                return 1;
            }
            fieldsInput = 1;
        }
        else if (strcmp(arg, "-d") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Bei -d Bitte trennzeichen angeben.\n");
                return 0;
            }
            i++;
            if (strlen(argv[i]) != 1)
            {
                fprintf(stderr, "Trennezcihen darf nur ein zeichen sein.\n");
                return 0;
            }
            config->inDelimiter = argv[i][0];
        }
        else if (strcmp(arg, "-o") == 0)
        {
            if (i + 1 >= argc)
            {
                fprintf(stderr, "Bei Verwendung von -o bitte Trennzeichen angeben.\n");
                return 0;
            }
            i++;
            if (strlen(argv[i]) != 1)
            {
                fprintf(stderr, "Trennezcihen darf nur ein zeichen sein.\n");
                return 0;
            }
            config->outDelimiter = argv[i][0];
        }
        else if (strcmp(arg, "-q") == 0)
        {
            config->besteFunktion = 1;
        }
        else if (strcmp(arg, "-H") == 0 || strcmp(arg, "--header") == 0)
        {
            config->header = 1;
        }
        else if (strcmp(arg, "-s") == 0)
        {
            config->ignoreLines = 1;
        }
        else if (strcmp(arg, "--strict") == 0)
        {
            config->strict = 1;
        }
        else
        {
            config->file = argv[i];
        }
    }

    if (!fieldsInput)
    {
        fprintf(stderr, "Keine Spalten angegeben.\n");
        return 0;
    }
    return 1;
}

int getFields(char* str_fields, Config* config)
{
    char* str_fields_cpy = "";
    strcpy(str_fields_cpy, str_fields);

    char* strToken = strtok(str_fields_cpy, &config->inDelimiter);

    while (strToken != NULL)
    {
        if (config->fieldcounter >= MAXFIELDS)
        {
            fprintf(stderr, "Zu viele Felder angeben. Max %d felder angeben.\n", MAXFIELDS);
            return 0;
        }

        int fieldNum = atoi(strToken);
        if (fieldNum < 1)
        {
            fprintf(stderr, "Fehlerhafte Spaltenangabe.\n");
            return 0;
        }
        config->fields[config->fieldcounter] = &fieldNum;
        config->fieldcounter++;
    }
    if (config->fieldcounter == 0)
    {
        fprintf(stderr, "Keine Felder angegeben.\n");
        return 0;
    }
    return 1;
}

void version()
{
    //todo
    //print version stuff
    printf("Show Version\n");
}

void help(char* progName)
{
    //todo
    //print help stuff
    printf("Show Help\n");
}

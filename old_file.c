#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#define OPT_FIELD                                  (1<<0)
#define OPT_IN_DELIMITER                  (1<<1)
#define OPT_OUT_DELIMITER               (1<<2)
#define OPT_QUOTES                              (1<<3)
#define OPT_HEADER                               (1<<4)
#define OPT_SUPPRESS                           (1<<5)
#define OPT_STRICT                                (1<<6)
#define OPT_HELP                                    (1<<7)
#define OPT_VERSION                            (1<<8)

typedef struct
{
    char inDelimiter;
    char outDelimiter;
    char suppressDelimiter;
} Options;

static const struct option long_options[] = {
    {"f", required_argument, 0, 'f'},
    {"d", optional_argument, 0, 'd'},
    {"o", optional_argument, 0, 'o'},
    {"q", optional_argument, 0, 'q'},
    {"header", optional_argument, 0, 'H'},
    {"s", optional_argument, 0, 's'},
    {"strict", optional_argument, 0, 'S'},
    {"help", optional_argument, 0, 'h'},
    {"version", required_argument, 0, 'V'},
    0
};

void parseFieldArguments(char* input, int* valOfToken);

int main(int argc, char* argv[])
{
    Options options;
    unsigned int flags = 0;
    //FILE* csvFile = fopen()

    int index = 0;
    int opt = 0;
    int valOfToken[100];

    char* directory;

    while ((opt = getopt_long(argc, argv, "f:d::o::q::H::s::h::", long_options, &index)) != -1)
    {
        switch (opt)
        {
            case 'd':
                char* arg = optarg;

                if (arg == NULL && optind < argc)
                {
                    // Make sure it's not another option
                    if (argv[optind][0] != '-')
                    {
                        arg = argv[optind];
                        optind++;
                    }
                }
                if (arg)
                {
                    // ignore quotes
                    if (arg[0] == '\'' || arg[0] == '"')
                    {
                        options.outDelimiter = arg[1];
                    }
                    else
                    {
                        options.outDelimiter = arg[0];
                    }
                    flags |= OPT_OUT_DELIMITER;
                    printf("args:%c\n", options.outDelimiter);
                }
                else
                {
                    options.outDelimiter = ',';
                }

                flags |= OPT_OUT_DELIMITER;
                break;
            case 'o':
                flags |= OPT_IN_DELIMITER;
                options.inDelimiter = optarg[0];
                break;
            case 'q':
                flags |= OPT_QUOTES;
                break;
            case 'H':
                flags |= OPT_HEADER;
                printf("Header\n");
                break;
            case 's':
                flags |= OPT_SUPPRESS;
                options.suppressDelimiter = optarg[0];
                break;
            case 'h':
                flags |= OPT_HELP;
                break;
            case 'f':
                flags |= OPT_FIELD;
                printf("args: %s\n", optarg);
                parseFieldArguments(optarg, valOfToken);
                break;
            //strict
            case 'S':
                flags |= OPT_STRICT;
                break;
            //version
            case 'V':
                flags |= OPT_VERSION;
                printf("version");
                break;
            default:
                break;
        }
    }

    //optind contains the index of the next element to be proccessed in argv
    if (optind < argc)
    {
        directory = argv[optind];
        printf("directory: %s\n", directory);
    }
    else
    {
        printf("hello\n");
        char buffer[1024];

        while (fgets(buffer, sizeof(buffer), stdin))
        {
        }
        directory = ".";
    }

    return 0;
}

void parseFieldArguments(char* input, int* valOfToken)
{
    if (input == NULL)
    {
        //error
        printf("error\n");
        return;
    }

    if (strlen(input) == 0)
    {
        //error
        printf("error\n");
        return;
    }
    int tokenCount = 0;
    char* inputCopy = (char*)malloc(sizeof(char) * strlen(input) + 1);

    strncpy(inputCopy, input, strlen(input));
    inputCopy[strlen(input)] = '\0';

    char* split = strtok(inputCopy, ",");
    valOfToken[tokenCount] = atoi(split);
    ++tokenCount;
    printf("token: %s\n", split);

    while ((split = strtok(NULL, ",")) != NULL)
    {
        //do stuff for all tokens after the first one
        valOfToken[tokenCount] = atoi(split);
        ++tokenCount;
        printf("token: %s\n", split);
    }

    printf("token count: %d\n", tokenCount);

    for (int i = 0; i < tokenCount; ++i)
    {
        printf("val of token: %d\n", valOfToken[i]);
    }

    free(inputCopy);
}

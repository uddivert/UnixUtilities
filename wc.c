#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * @brief returns the number of lines in the file
 * depending by counting retunrs
 * 
 * @param filename the file name being used
 * @return int the number of lines
 */
int lines(char *filename)
{
    FILE *pFile;
    pFile = fopen(filename, "r");
    if (pFile == NULL)
    {
        perror("Error:");
        return EXIT_FAILURE;
    } // if
    else
    {
        char ch;
        int counter = 0;
        while ((ch = fgetc(pFile) != EOF))
        {
            if (ch == '\n')
                counter++;
        } // while
        fclose(pFile);
        return counter;
    } // else
}

/**
 * @brief returns the number of words in a file
 * by counting the number of spaces and line breaks
 * 
 * @param filename the file name being tested for
 * @return int the number of words
 */
int words(char *filename)
{
    FILE *pFile;
    pFile = fopen(filename, "r");
    if (pFile == NULL)
    {
        perror("Error:");
        return EXIT_FAILURE;
    } // if
    else
    {
        char ch;
        int counter = 0;
        while ((ch = fgetc(pFile) != EOF))
        {
            if (ch == '\n' || ch == ' ')
                counter++;
        } // while
        fclose(pFile);
        return counter;
    } // else
}

/**
 * @brief returns the file size in bytes
 * 
 * @param filename is the filename being tested
 * @return int is the size of bytes
 */
int bytes(char *filename)
{
    struct stat stats;
    if (stat(filename, &stats) == 0)
    {
        perror("Error:");
        return EXIT_FAILURE;
    }
    else
    {
        int size = stats.st_size;
        return size;
    } // else
}

/**
 * @brief main method that determines which method to used
 * 
 * @param argc number of flags inputted
 * @param argv the flags inputted. Should be c, l, w, or filename
 * @return int exit code
 */
int main(int argc, char *argv[])
{
    int opt;

    if (argv[optind] == NULL)
    {
        printf("wc requires an argument\n");
        return EXIT_FAILURE;
    }

    while ((opt = getopt(argc, argv, "clw")) != -1)
    {
        switch (opt)
        {
        case 'c':
            printf("Option c was provided\n");
            break;
        case 'l':
            printf("Option l was provided\n");
            break;
        case 'w':
            printf("Option w was provided\n");
            break;
        case 1:
            printf("error");
            return 1;
        }
    }
    return 0;
}
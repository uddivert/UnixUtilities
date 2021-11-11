#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
/**
 * @brief copies input files to standard output. Copying ends at the point in 
 * each input file indicated by the -c number or -n number option. Option argument
 * is counted in units of lines or bytes, according to the options -n and -c
 * respectively. Both line and byte counters start from 1. If no options are specified,
 * -n defaults to 10. If no files are specified or when one of the files i -, standard
 * input is assumed.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{

    int length = 10;
    int parseByLine = 1;

    // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
    // parse args with getopt and
    int index;
    int c;
    opterr = 0;

    // loop through all args and set values for length and whether to parse by line or
    // to parse by bytes
    while ((c = getopt(argc, argv, "c:n:")) != -1)
        switch (c)
        {
        case 'c':
            length = atoi(optarg);
            parseByLine = 0;
            break;
        case 'n':
            length = atoi(optarg);
            parseByLine = 1;
            break;
        }

    //consider all remaining arguments to be files
    for (index = optind; index < argc; index++)
    {
        int fd;
        if (strcmp(argv[index], "-") == 0)
        {
            fd = STDIN_FILENO;
        }
        else
        {
            char *filename = argv[index];
            fd = open(filename, O_RDONLY);
        }
        int n;
        int counter = 0;
        char buffer[1];

        while ((n = read(fd, buffer, 1)) > 0 && counter < length)
        {
            if (parseByLine == 1 && buffer[0] == '\n')
                counter++;
            else if (parseByLine != 1)
                counter++;

            write(STDOUT_FILENO, buffer, n);
        } // while

        if (n == -1)
            perror("read");

        close(fd);
    }
    return 0;
} // main

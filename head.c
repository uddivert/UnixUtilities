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
    // turns off the buffer for printf
    setbuf(stdout, NULL);
    int length = 10;
    int parseByLine = 1;

    // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
    // parse args with getopt
    int index;
    int c;
    int remainingArgs = argc-1;
    opterr = 0;

    // loop through all args and set values for length and whether to parse by line or
    // to parse by bytes
    while ((c = getopt(argc, argv, "c:n:")) != -1)
    {
        remainingArgs--;
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
    }
    // consider all remaining arguments to be files
    for (index = optind; index < argc; index++)
    {
        int fd;
        int n;
        int counter = 0;
        char buffer[1];

        if (strcmp(argv[index], "-") == 0)
        {
            fd = STDIN_FILENO;
            if (remainingArgs > 1)
                printf("==> standard input <==\n");
        }
        else
        {
            char *filename = argv[index];
            fd = open(filename, O_RDONLY);
            if (fd < 0)
            {
                perror(filename);
                continue;
            }
            if (remainingArgs > 1)
                printf("==> %s <==\n", filename);
        }

        do
        {
            n = read(fd, buffer, 1);
            if (parseByLine == 1 && buffer[0] == '\n')
                counter++;
            else if (parseByLine != 1)
                counter++;

            write(STDOUT_FILENO, buffer, n);
        } while (counter < length && n > 0);

        if (n == -1)
            perror("read");

        close(fd);
    }
    return 0;
}

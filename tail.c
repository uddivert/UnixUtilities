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
    int remainingArgs = argc - 1;
    opterr = 0;

    // loop through all args and set values for length and whether to parse by line or
    // to parse by bytes
    while ((c = getopt(argc, argv, "c:n:")) != -1)
    {
        remainingArgs -= 2;
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
        char buffer[1];

        if (strcmp(argv[index], "-") == 0)
        {
            fd = STDIN_FILENO;
            if (remainingArgs > 1)
                printf("==> standard input <==\n");

            char bigBuffer[1000];
            int position = 0;
            while ((n = read(fd, buffer, 1)) > 0)
            {
                bigBuffer[position] = buffer[0];
                position++;
            }
            if (parseByLine == 0)
            {
                for (int i = position - length; i < position; i++)
                {
                    printf("%c", bigBuffer[i]);
                }
            }
            else
            {
                int lines = 0;
                for (int i = 1000; i >= 0; i--)
                {
                    if (bigBuffer[i] == '\n')
                        lines++;
                    if (lines == length)
                    {   
                        i++;
                        while (i < position)
                        {
                            printf("%c", bigBuffer[i]);
                            i++;
                        }
                        i = 0;
                        lines = -1;
                    }
                }
                if (lines != -1)
                {
                    int i = 0;
                    while (i < position)
                    {
                        printf("%c", bigBuffer[i]);
                        i++;
                    }
                }
            }
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
            //get file size
            off_t size = lseek(fd, 0, SEEK_END);
            if (size == -1)
                perror("lseek");

            if (parseByLine == 0) // -c option
            {
                //skip to size - length
                lseek(fd, size - length, 0);
            }
            else //-n option (default)
            {
                int offset = 0;
                for (int linesPassed = 0; linesPassed < length && size + offset > 0; offset--)
                {
                    //move endoffile - offset
                    lseek(fd, offset, SEEK_END);
                    read(fd, buffer, 1);
                    if (buffer[0] == '\n')
                    {
                        linesPassed++;
                    }
                }
                if (size + offset == 0)
                    lseek(fd, 0, 0);
            }

            //print remainder of file
            while ((n = read(fd, buffer, 1) > 0))
                printf("%c", buffer[0]);

            if (n == -1)
                perror("read");
        }
        close(fd);
    }
    return 0;
}
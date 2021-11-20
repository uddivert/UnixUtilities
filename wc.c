#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief reads input files from parameters and writes the number of new lines,
 * words, and bytes, in that order, contained in each input file to standard output
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    // turn off the buffer for printf
    setbuf(stdout, NULL);

    int cflag = 0, lflag = 0, wflag = 0, opt;
    int cTotal, lTotal, wTotal;
    opterr = 0;

    //set flags from args
    while ((opt = getopt(argc, argv, "clw")) != -1)
    {
        switch (opt)
        {
        case 'c':
            cflag = 1;
            break;
        case 'l':
            lflag = 1;
            break;
        case 'w':
            wflag = 1;
            break;
        } // switch
    }

    //if no flags are ticked, tick all flags
    if (cflag + lflag + wflag == 0)
        cflag = lflag = wflag = 1;

    //assume all other args are files
    for (int index = optind; index < argc; index++)
    {
        int fd, n, size;
        char *filename = argv[index];
        char buffer[1];
        int l = 0, w = 0;
        int stdinFlag = 0;
        if (strcmp(argv[index], "-") == 0)
        {
            fd = STDIN_FILENO;
            stdinFlag = 1;
        }
        else
        {
            fd = open(filename, O_RDONLY);
        }

        // loop through
        if (lflag || wflag)
        {
            int newWord = 0;
            while ((n = read(fd, buffer, 1)) > 0)
            {
                if (buffer[0] == ' ' ||
                    buffer[0] == '\t' ||
                    buffer[0] == '\n' ||
                    buffer[0] == '\0')
                {
                    if (buffer[0] == '\n' || buffer[0] == '\0')
                        l++;
                    newWord = 1;
                }
                else if (buffer[0] == EOF)
                {
                    w++;
                }
                else if (newWord == 1)
                {
                    if (w == 0)
                        w++;
                    w++;
                    newWord = 0;
                }
                if (cflag == 1)
                    size++;
            }
            if (newWord == 1)
                w++;
        } // while

        //print output
        if (lflag)
        {
            lTotal += l;
            printf("%4d ", l);
        }
        if (wflag)
        {
            wTotal += w;
            printf("%4d ", w);
        }
        if (cflag == 1)
        {
            if (stdinFlag == 0)
            {
                size = lseek(fd, 0, SEEK_END);
                if (size == -1)
                    perror("lseek");
            }

            cTotal += size;
            printf("%4d ", size);
        }
        printf("%s\n", filename);
    }
} // main
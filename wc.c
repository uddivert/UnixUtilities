#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
        int fd, n;
        char *filename;
        char buffer[1];

        int l = 0, w = 0;
        if (strcmp(argv[index], "-") == 0)
        {
            fd = STDIN_FILENO;
        }
        else
        {
            filename = argv[index];
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
                if (newWord == 1)
                {
                    w++;
                    newWord = 0;
                }
            }
        } // while

        //print output
        if (lflag)
        {
            lTotal += l;
            printf("  %i", l);
        }
        if (wflag)
        {
            wTotal += w;
            printf(" %i ", w);
        }
        if (cflag == 1)
        {
            off_t size = lseek(fd, 0, SEEK_END);
            if (size == -1)
                perror("lseek");
            cTotal += size;
            printf(" %li ", size);
        }
        printf("%s\n", filename);
    }
} // main
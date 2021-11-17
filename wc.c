#include <stdio.h>
#include <unistd.h>

// needs  -clw [ files

// Prototypes
int lines();
int words();
int bytes();

/*
int lines() { return 0;}
int words () { return 0;}
int bytes() { return 0;}
*/

int main (int argc, char *argv[]) {
    int option;
    while((option = getopt(argc, argv, ":clw:")) != -1)
    {
        switch(option) {
            case ':': 
                printf("initial");
                break;
            case 'c':
                printf("case c\n");
                break;
            case 'l':
                printf("case l\n");
                break;
            case 'w': 
                printf("case w\n");
                break;
            default:
                printf("invalid option\n");
                return 1;
        } // switch
        return 0;
    }
} // main
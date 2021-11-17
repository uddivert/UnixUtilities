#include <stdio.h>
#include <stdlib.h>
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
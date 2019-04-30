#include "process.h"
#include "memory.h"
using namespace std;


void userInput(int & memSize, int & pageSize, string & nameFile)
{
    char buf[10];
    bool invalid = true;

    do
    {

        do {
            printf("Memory size: ");
            sscanf(buf, "%d", mem);
            if ( mem <= 0)
            {
                clear_stdin(buf);
                printf("ERROR: You didn't enter a number!\n");
                invalid = true;
            }
            else
            {
              invalid = false;
            }
          } while(invalid);



            do {
                printf("Page size (1: 100, 2: 200, 3: 400): ");
                sscanf(buf, "%d", page);
                if ( page < 1 && page > 3)
                {
                    clear_stdin(buf);
                    printf("ERROR: You didn't enter a number!\n");
                    invalid = true;
                }
                else
                {
                  invalid = false;
                }

              } while(invalid);

        switch (page)
        {
        case 1: page = 100; break;
        case 2: page = 200; break;
        case 3: page = 400; break;
        }

        if ((mem) % (page) == 0)
        {
            invalid = true;
            printf("ERROR: Memory size must be a multiple of the page!");
            printf(" %d is not a multiple of %d, please retry.\n", *mem, *page);
        }

    }while(invalid);

  do {
      printf("Input file: ");
      sscanf(buf, "%s", nameFile);

      if (!(ifile = fopen(nameFile, "r")))
      {
            perror("ERROR: Could not open file!\n");
            invalid = true;
      }
      else
      {
            invalid = false;
      }
    } while(invalid);

}

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

// MAIN STDIN
// int main(void)
// {
//     char    *next_line;
//     int     count;

//     count = 0;
//     printf("Please enter text (Ctrl+D to end input):\n");

//     while (1)
//     {
//         next_line = get_next_line(STDIN_FILENO);
//         if (next_line == NULL)
//             break ;
//         count++;
//         printf("Line %d: %s", count, next_line);
//         free(next_line);
//     }
//     printf("\nEnd of input reached.\n");
//     return (0);
// }

// MAIN LOOP
// int main(void)
// {
//   int    fd;
//   char  *next_line;
//   static int  count;

//     count = 0;
//     fd = open("../file-examples/spaces_after_1/1.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         printf("Error opening da thing");
//         return (1);
//     }
//     while (1)
//     {
//         next_line = get_next_line(fd);
//         if (next_line == NULL)
//             break ;
//         count++;
//         printf("\n\nmain[%d]:%s\n\n", count, next_line); 
        
//         //next_line = NULL;
//         free(next_line);
//     }
//     close(fd);
//     printf("CONGRATS, FILE WAS READED");
//     return (0);
// }

// MAIN GET ONE LINE
// TODO: ¿si solo leo una línea y no más porque por ejemplo DA ERROR, es correcto que no cuadre allocs y frees??? 
int main(void)
{
  int    fd;
  char  *next_line;
  static int  count;

    count = 0;
    fd = open("../file-examples/spaces_after_1/1.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening da thing");
        return (1);
    }
    next_line = get_next_line(fd);
    count++;
    printf("\n\nmain[%d]:%s\n\n", count, next_line); 
    free(next_line);
    next_line = NULL;
    close(fd);
    printf("GO CHECK VALGRIND");
    return (0);
}

// /home/codespace/francinette/tester.sh
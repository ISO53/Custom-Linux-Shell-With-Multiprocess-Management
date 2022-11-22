#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOKENS_SIZE 6

int main(int argc, char **argv)
{

    if (argc != TOKENS_SIZE)
    {
        printf("Too few arguments in function call! For additional information try 'help execx'.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-t") != 0)
    {
        printf("The function execx has no argument as '%s'!. Did you mean '-t'?\n", argv[1]);
        return EXIT_FAILURE;
    }

    int number = atoi(argv[2]);
    if (number == 0 || number == -1)
    {
        printf("Third parameter should be a positive integer! For additional information try 'help execx'.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[4], "-f") != 0)
    {
        printf("The function writef has no argument as '%s'!. Did you mean '-f'?\n", argv[4]);
        return EXIT_FAILURE;
    }

    // Call the process number of times given by the user
    for (int i = 0; i < number; i++)
    {
        int process;

        pid_t pid;
        if ((pid = fork()) == 0)
        { // Child process

            // [0] = execx, [1] = -t, [2] = n, [3] = processName, [4] = -f, [5] = fileName
            char *data[4] = {argv[3], argv[4], argv[5], NULL};
            process = execv(argv[3], data);

            perror("Error occured during progress! Aborting process.\n");
            return EXIT_FAILURE;
        }
        else
        { // Parent process
            wait(&process);
        }
    }

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MIN_TOKENS_SIZE 6

void execProcess(int number, char *processName, char **data);
void printStrArr(int n, char **matrix);
void copyMatrixFrom(int start, int end, char **arr1, char **arr2);

// Main method
int main(int argc, char **argv)
{

    if (argc < MIN_TOKENS_SIZE)
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

    /* given input is --> [0] = execx, [1] = -t, [2] = n, [3.4.5.6...] = parameters
     * we should send the parameters, so first 3 string is off the table
     */
    int dataSize = argc - 3;
    char *data[++dataSize]; // +1 is because NULL for last element
    copyMatrixFrom(3, argc, data, argv);
    data[dataSize - 1] = NULL;

    if ((strcmp(data[0], "writef") == 0) || (strcmp(data[0], "execx") == 0)) {
        execProcess(number, data[0], data);
    } else {
        printf("There is no program called %s! Aborting process.", data[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Executes a process with a given 'processName', 'number' times with given 'data'
void execProcess(int number, char *processName, char **data)
{
    // Call the process number of times given by the user
    for (int i = 0; i < number; i++)
    {
        int process;

        pid_t pid;
        if ((pid = fork()) == 0)
        { // Child process

            process = execv(processName, data);

            perror("Error occured during progress! Aborting process.\n");
            return;
        }
        else
        { // Parent process
            wait(&process);
        }
    }
}

// Prints given string arr
void printStrArr(int n, char **matrix)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", matrix[i]);
    }
}

// Copies arr2's elements to arr1 starting from 'start''th index to 'end''th index.
void copyMatrixFrom(int start, int end, char **arr1, char **arr2)
{
    for (int i = start; i < end; i++)
    {
        arr1[i - start] = arr2[i];
    }
}

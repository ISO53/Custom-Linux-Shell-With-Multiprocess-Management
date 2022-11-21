#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void getSystemTime(char *timeStr);

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        printf("Too few arguments in function call! Try 'help writef'.\n");
        exit(EXIT_FAILURE);
    }

    if (argc > 3)
    {
        printf("Too many arguments in function call! Try 'help writef'.\n");
        exit(EXIT_FAILURE);
    }

    char *mode = argv[1];

    if (strcmp(mode, "-f") != 0)
    {
        printf("The function writef has no argument as '%s'!. Did you mean '-f'?\n", mode);
        exit(EXIT_FAILURE);
    }

    char *fileName = argv[2];

    FILE *fp = fopen(strcat(fileName, ".txt"), "a+");
    if (fp)
    {
        char message[256];
        char timeStr[128];
        getSystemTime(timeStr);
        snprintf(message, sizeof(message), "time:%s | pid:%d | ppid:%d\n", timeStr, getpid(), getppid());
        if (fputs(message, fp) == EOF) {
            printf("Failed to write file '%s'! Aborting process.\n", fileName);
            exit(EXIT_FAILURE);
        }

        char directory[1024];
        getcwd(directory, sizeof(directory));
        printf("Message succesfully written to the file located in '%s'.\n", directory);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Failed to open file '%s'! Aborting process.\n", fileName);
        exit(EXIT_FAILURE);
    }
}

// Returns current date and time as string format
void getSystemTime(char *timeStr)
{
    time_t raw_time;
    struct tm *timeinfo;
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    strcpy(timeStr, asctime(timeinfo));
    timeStr[strlen(timeStr) - 1] = '\0';
}


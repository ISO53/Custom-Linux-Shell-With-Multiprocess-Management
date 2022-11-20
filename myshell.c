#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

#define FALSE 0
#define TRUE 1
#define SIZE 1024
#define RUNNING 1
#define CLOSING 0
#define MYSHELL_STR "\nmyshell >> "

void init_myshell();
void printDirectory();
int takeInput(char *string);
void handleInputs(char *string);
int startsWith(char *str1, char *str2);

int status = RUNNING;

// Main method
int main()
{
	char userInput[SIZE];

	init_myshell();

	while (status == RUNNING)
	{
		// Infinite loop waiting for user input

		if (takeInput(userInput) == FALSE)
		{
			// User didn't enter any input. Carry on to the endless loop.
			continue;
		}

		// User entered an input! Input is in (userInput).

		handleInputs(userInput);
	}
}

// Initializes myshell program
void init_myshell()
{
	// Welcomes to current user.
	char *userName = getenv("USER");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Welcome %s to myshell!", userName);
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

// Prints current directory
void printDirectory()
{
	char directory[SIZE];
	getcwd(directory, sizeof(directory));
	printf("%s", directory);
}

// Reads line from stdin (terminal)
int takeInput(char *string)
{
	char *userInput;

	// userInput = readline("\nmyshell >> ");
	userInput = readline(MYSHELL_STR);

	if (strlen(userInput) >= 0)
	{
		strcpy(string, userInput);
		return TRUE;
	}

	return FALSE;
}

// Handles the inputs given by user
void handleInputs(char *input)
{
	if (strcmp(input, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(input, "bash") == 0)
	{
		// Runs bash inside our myshell
		system("/bin/bash");
	}
	else if (strcmp(input, "change") == 0)
	{
		// Changes system shell as bash (default). May ask password.
		system("chsh -s /bin/bash");
	}
	else if (strcmp(input, "clear") == 0)
	{
		// Clears the screen
		system("clear");
	}
	else if (startsWith(input, "cat ") == TRUE)
	{
		// Writes cat and what comes after
		printf("cat:%s", &input[3]);
	}
}

// Return true if str1 starts with str2
int startsWith(char *str1, char *str2)
{
	return strncmp(str1, str2, strlen(str2)) == 0;
}

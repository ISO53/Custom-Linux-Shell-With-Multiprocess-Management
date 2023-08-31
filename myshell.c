#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <readline/readline.h>

#define FALSE 0
#define TRUE 1
#define SIZE 1024
#define RUNNING 1
#define CLOSING 0
#define MYSHELL_STR "\nmyshell >> "
#define TOKENS_SIZE 6

void init_myshell();
void getDirectory(char *dir);
int takeInput(char *string);
void handleInputs(char *string);
int startsWith(char *str1, char *str2);
void printFilesInDir();
void printHelp(char *input);
int tokenizeInput(char *input, char **tokens, int length);

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

	return EXIT_SUCCESS;
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

// Returns current directory
void getDirectory(char *dir)
{
	char directory[SIZE];
	getcwd(directory, sizeof(directory));
	strcpy(dir, directory);
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
	else if (strcmp(input, "ls") == 0)
	{
		printFilesInDir();
	}
	else if (startsWith(input, "help") == TRUE)
	{
		printHelp(input);
	}
	else if (startsWith(input, "execx ") == TRUE)
	{
		char *tokens[TOKENS_SIZE];
		tokenizeInput(input, tokens, TOKENS_SIZE);

		int process;

		pid_t pid;
		if ((pid = fork()) == 0)
		{ // Child process

			// [0] = execx, [1] = -t, [2] = n, [3] = processName, [4] = -f, [5] = fileName
			char *data[7] = {tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], NULL};
			process = execv("execx", data);

			perror("Error occured during progress! Aborting process.\n");
			return;
		}
		else
		{ // Parent process
			wait(&process);
		}
	}
	else
	{
		printf("Incorrect command! Please type help for additional information.\n");
		return;
	}
}

// Return true if str1 starts with str2
int startsWith(char *str1, char *str2)
{
	return strncmp(str1, str2, strlen(str2)) == 0;
}

// Prints files and dirs in the current directory except . and ..
void printFilesInDir()
{
	DIR *d;
	struct dirent *dir;
	char dirStr[1024];
	getDirectory(dirStr);
	d = opendir(dirStr);

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0))
			{
				printf("%s ", dir->d_name);
			}
		}
		closedir(d);
	}
	else
	{
		printf("Problem occured while opening dir '%s'.", dirStr);
	}
}

/**
 * @brief Prints help informations
 * 
 * @param input 
 */
void printHelp(char *input)
{
	if (strcmp(input, "help") == 0)
	{
		printf("Available commands are:\nbash, cat, change, clear, execx, exit, help, ls\nPlease type 'help commandName' for additional information.\n");
	}
	else if (strcmp(input, "help bash") == 0)
	{
		printf("Opens the bash shell to use bash commands.\n");
	}
	else if (strcmp(input, "help cat") == 0)
	{
		printf("Prints the input to the screen.\n");
	}
	else if (strcmp(input, "help change") == 0)
	{
		printf("Added for emergencies. Changes system shell to /bin/bash. The system must be restarted for the change to take effect.\n");
	}
	else if (strcmp(input, "help clear") == 0)
	{
		printf("Clear the terminal.\n");
	}
	else if (strcmp(input, "help execx") == 0)
	{
		printf("Executes the given process certain times. The exact syntax is:\nexecx -t {n} {name} {[parameters]}\n");
		printf("Here the n is how many times the process should be executed.\n");
		printf("The name should be the name of the process and the parameters will used as parameters of called process.\n");
	}
	else if (strcmp(input, "help exit") == 0)
	{
		printf("Exits shell.\n");
	}
	else if (strcmp(input, "help help") == 0)
	{
		printf("Shows the available commands and what they do.\n");
	}
	else if (strcmp(input, "help ls") == 0)
	{
		printf("Prints the directories and files under the current directory except '.' and '..'.\n");
	}
}

/** Tokenizes the given input into an array of strings and returns the number
 * of tokenized elements. If the number doesnt match the length, than there is
 * less token than the given arrays size.
 */
int tokenizeInput(char *input, char **tokens, int length)
{
	int counter = 0;
	char *temp = strtok(input, " ");

	while (temp != NULL && counter < length)
	{
		tokens[counter++] = temp;
		temp = strtok(NULL, " ");
	}

	return counter;
}

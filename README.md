# MyShell
MyShell is a Linux shell program that i have written in C, designed to function as a terminal program on your system. MyShell includes custom commands, responses, and error messages.

# Installation
To install MyShell, follow these steps:

+ Clone the MyShell repository to your local machine.
+ Open a terminal window and navigate to the MyShell directory.
+ Compile MyShell by running the command `make`.
+ Then type `./myshell`

# Usage
MyShell is designed to function like a standard Linux shell program, with a few custom commands added. Here are the custom commands included in MyShell:

+ **exit:** Exits the MyShell program.
+ **bash:** Calls the default bash shell and allows you to execute bash commands. Returns to MyShell when you type exit.
+ **execx:** Runs the specified program a given number of times in the background, waiting for each process to finish before continuing. Additional parameters are passed to the program.
+ **writef:** Writes the system time, process ID, and parent process ID to a file. If the file does not exist, it will be created. If the file exists, the data will be appended to the end of the file.
+ **cat message:** Returns the message.
+ **clear:** Clears the terminal screen.
+ **ls:** Lists all files in the current directory.

# Project Functions
Let's start with execx. execx command allows you to call a program any number of times. In this case its writef. Here is how you can do it:
```
execx -t [number] [program_name] [program_parameters]
writef -f [file_name]
```
these are the sytnaxes for execx and writef programs. Here how you can use these. Example:
```
execx -t 3 writef -f foo
```
this command will write the `system time`, `pid` and `ppid` value in a single line into the file named `foo` three times. You can also call execx program in execx program. Example:
```
execx -t 3 execx -t 5 writef -f foo
```
First execx command will call `execx -t 5 writef -f foo` three times and than second execx command will call `writef -f foo` 5 times. You can call as many nested commands as you want as long as you do not exceed the maximum number of arguments **(100)**. You can change this value from the myshell.c file.

# Error Handling
MyShell will return an error message if you enter an invalid command or if there is an error with a called program. You can always type help to get help.

# First Time?
If you are confused while using the program, you can run the `help` command like this
```
help
```
or like this
```
help command_name
```

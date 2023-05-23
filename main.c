#include "header.h"

#define MAX_CMD_LEN 1024 // Define a constant for the maximum length of a command

int main(int argc, char **argv)
{
    signal(SIGINT, sigintHandler);
    ssize_t inputCommand;  // Declare a variable to store the size of the input command
    pid_t pid;             // Declare a variable to store the process ID
    char *command = NULL;  // Declare a pointer for the input command
    size_t bufsize = 0;    // Declare a variable to store the buffer size for the input command
    extern char **environ; // Declare an external pointer to the environment variables
    char *path = getenv("PATH");
    // Declare a pointer to the PATH environment variable and stores all the environment variables in the path variable
    char path_copy[strlen(path) + 1];

    unsigned long loopCount = 1;
    // Declare a variable to store the number of times the loop has been executed. In case of an error the number of times the the user has supplied a command needs to printed to the screen. This variable keeps track of that.
    int interrupted = 0;
    while (1) // Begin an infinite loop
    {

        if (isatty(STDIN_FILENO))
        // the isatty function is for checking if the program is in interactive mod or not. If it is interactive mode print the prompts and if not dont print the prompts.
        {
            {
                _putchar('$');  // Print a prompt
                _putchar(' ');  // Print a prompt
                fflush(stdout); // Flush the output buffer
            }
        }

        inputCommand = getline(&command, &bufsize, stdin); // Read the input command from the user

        if (inputCommand == -1) // Check if there was an error reading the input command
        {
            /* End of file or error, exit the loop */
            break; // Break out of the loop
        }

        /* Remove the trailing newline character */
        if (stringlength(command) > 1)
        {
            command[inputCommand - 1] = '\0';
        }
        else
        {
            command[0] = '\0';
            continue;

        }

        if (builtin_functions(argv, command) == 1)
        {
            continue;
        }

        /* Split the command into arguments */
        char *arg = strtok(command, " ");
        // Split the input command into arguments using the strtok function b using the delimiter "whitespace" into tokens. the strtok functions stores the first of the splitted arguments in the arg variable.
        char *args[MAX_CMD_LEN]; // Declare an array to store the arguments
        int i = 0;               // Declare a variable to keep track of the number of arguments

        while (arg != NULL)
        // Loop through each argument in the arg value consisting of the tokens.
        {
            args[i] = arg; // Store the current token in the args array.
            arg = strtok(NULL, " ");
            // Move to the next argument because if the the strtok function is called again after the first call it returns the next token.
            i++; // Increment the number of arguments
        }

        args[i] = NULL; // Set the last argument to NULL
        struct stat sb;
        // Declare a struct sb to hold information about the file

        if (stat(args[0], &sb) == 0 && sb.st_mode & S_IXUSR)
        // this condition is used to get information about the filein the args[0] variable. The information is stored in a struct stat(sb) and the next condition performs a bitwise operation to check if the user has the right permission to execute the file. This will confirm that the command given is a path to a file and the file is executable
        {
            char command_path[MAX_CMD_LEN];       // Declare a character array to hold the command path
            sprintf(command_path, "%s", args[0]); // Copy the command path into the character array
            goto command_found;                   // Jump to the command_found label
        }

        /* Search for the command in the PATH */
        strcpy(path_copy, path);
        // Copies the original PATH environment variable to a new character array path_copy

        char *dir = strtok(path_copy, ":"); // Split the PATH environment variable into directories

        char command_path[MAX_CMD_LEN];
        // Declare a character array to hold the full absolute command path

        while (dir != NULL)

        {
            // Open the current directory
            DIR *d = opendir(dir);
            if (d != NULL)
            {
                struct dirent *entry;
                // the struct dirent is a structure for holding informating regarding to the entry to a directory this allows us to access the contents of the directory.

                while ((entry = readdir(d)) != NULL)
                // Loop through all the files in the directory using the readdir function
                {
                    // Check if the current file matches the command name using the strcmp function
                    if (strcmp(entry->d_name, args[0]) == 0)
                    {
                        /* Found the command */
                        // Construct the full path of the command
                        sprintf(command_path, "%s/%s", dir, args[0]);

                        // Close the directory and jump to the command_found label
                        closedir(d);
                        goto command_found;
                    }
                }
                // Close the directory

                closedir(d);
            }
            // Move to the next directory in the PAT
            dir = strtok(NULL, ":");
        }

        /* Command not found */
        // Print an error message and continue to the next iteration of the loop
        print_errorStartString(argv, loopCount, args[0], "not Found");
        // This is a function i created in case an error occurs how the error statement should be printed to the screen
        _putchar('\n');
        loopCount++;
        continue;

    command_found:

        /* Fork a new process */
        // Fork a child process to execute the command
        pid = fork();

        if (pid == -1)
        {
            // Fork failed, print an error message and exit
            perror("fork failed\n");
            loopCount++;
            exit(1);
        }
        else if (pid == 0)
        {
            /* Child process is succesfully created*/
            // Execute the command in the child process
            int ret = execve(command_path, args, environ);
            // we use the execve function to execute the our function. The function takes either the absolute path or relative path which on our case is the command_path variable, then the args value supplies the function with the arguments to the function, then the environ represents the environment . which in our case is the external pointer to the environment i.e environ
            if (ret == -1)
            // in case an error occurs
            {
                // Execution failed, print an error message and exit
                print_errorStartString(argv, loopCount, args[0], NULL);
                // This is a function i created in case an error occurs how the error statement should be printed to the screen
                perror(""); // the perror function returns a user suplied string along the error message
                // Increment the loop counter and continue to the next iteration of the loop
                loopCount++;
                exit(1);
            }
        }
        else
        // the child process is succesfully created but we use the waitpid function to tell the program to wait for the execution of the command to finish before continuing of the program.
        {
            // Wait for the child process to finish
            int status;
            waitpid(pid, &status, 0);
        }
        // Increment the loop counter and continue to the next iteration of the loop
        loopCount++;
    }

    /*Free the memory allocated for the command buffer and return */
    free(command);
    return 0;
}

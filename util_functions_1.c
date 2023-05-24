#include "header.h"


/**
 * _putchar - writes a single character to stdout
 * @c: character to write
 * Return: the character
 **/
int _putchar(char c)
{
    return write(1, &c, 1);
}

/**
 * print_errorStartString - writes a custom error string
 * @argv: original argument string array which contains the file name
 * @loopCount : character to write
 * @command: character to write
 * @error: optional custom error message to be printed if the user wants to
 * Return: the character
 **/
void print_errorStartString(char **argv, unsigned long loopCount, char *command, char *error)
{

    int i = 0;
    int j = 0;
    const char *name = argv[0];

    while (name[i] != '\0')
    {
        _putchar(name[i]);
        i++;
    }

    _putchar(':');
    _putchar(' ');
    printNumber(loopCount);
    _putchar(':');
    _putchar(' ');

    for (i = 0; command[i] != '\n' && command[i] != '\0'; i++)
    {
        _putchar(command[i]);
    }

    _putchar(':');
    _putchar(' ');

    if (error != NULL)
    {
        for (j = 0; error[j] != '\n' && error[j] != '\0'; j++)
        {
            _putchar(error[j]);
        }
    }
}
/**
 * builtin_functions - for builtins
 * description: searches and compares to see if the command is a builtin
 * @argv: argv
 * @buffer: buffer
 * Return: 0
 */
int builtin_functions(char **argv, char *command)
{
    int i;

    builtins arr[] = {
        {"exit", u_exit},
        {'\0', NULL}};

    if (argv != NULL)
    {
        for (i = 0; arr[i].function; i++)
        {
            if (_strcmp(argv[0], "exit") == 0)
            {
                u_exit(command);
                return (1);
            }
            if (_strcmp(command, arr[i].function_desc) == 0)
            {
                arr[i].function();
                return (1);
            }
        }
    }
    return (0);
}

/**
 * u_exit - a custom exit function
 * @command: pointer to the command input
 * Return: the exit code
 **/
int u_exit(char *command)
{
    free(command);
    exit(1);
}

void sigintHandler(int sig_num)
{
    // Signal handling code goes here
    printf("\n");
    printf("$ ");
    fflush(stdout);
}

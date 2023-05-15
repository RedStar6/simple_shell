#include "header.h"

/**
 * _strcmp - compares two strings to see if they are the same
 * @s1: string 1
 * @s2: string 2
 * Return: s1[i] - s2[j] on failure or 0 on success
 **/
int _strcmp(char *s1, char *s2)
{
    int i = 0, j = 0;

    for (; s1[i] != '\0' || s2[j] != '\0'; i++, j++)
    {
        if (s1[i] != s2[j])
        {
            return (s1[i] - s2[j]);
        }
    }
    return (0);
}

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
void print_errorStartString(char **argv, int loopCount, char *command, char *error)
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
    _putchar(loopCount + '0');
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
            if (_strcmp(command, arr[i].function_desc) == 0)
            {
                arr[i].function(argv, command);
                return (1);
            }
        }
    }
    return (0);
}

int u_exit(char **argv, char *command)
{
    free(command);
    exit(1);
}

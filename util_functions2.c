#include "header.h"

/**
 * stringlength - gets the length of a string
 * @s: a string
 * Return: length of string
 **/
int stringlength(char *s)
{
    int i;

    for (i = 0; s[i] != '\0'; i++)
    {
    }
    return (i);
}

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
 * printNumber - converts number to string and prints to the screen
 * @number: number to convert
 * Return: void
 **/
void printNumber(unsigned long number)
{
    char *buffer = NULL;
    int length = 0;

    // Calculate the number of digits in the number
    unsigned long temp = number;
    do
    {
        temp /= 10;
        length++;
    } while (temp > 0);

    // Allocate memory for the string representation
    buffer = (char *)malloc((length + 1) * sizeof(char));
    if (buffer != NULL)
    {

    // Convert the number to a string
    for (int i = length - 1; i >= 0; i--)
    {
        buffer[i] = '0' + (number % 10);
        number /= 10;
    }
    buffer[length] = '\0'; // Null-terminate the string

    // Print the string character by character
    for (int i = 0; i < length; i++)
    {
        _putchar(buffer[i]);
    }
    }

    // Free the allocated memory
    free(buffer);
}
/**
 * print_env - prints the environment details
 * description: env builtin
 * Return: 0
 */
int print_env(void)
{
    int i;
    int j;

    char *string = NULL;

    for (i = 0; environ[i] != NULL; i++)
    {
    for (j = 0; environ[i][j] != '\0'; j++)
    {
        string = (&(environ[i][j]));
        write(STDOUT_FILENO, string, stringlength(string));
        break;
    }
    _putchar('\n');
    }
    return (0);
}
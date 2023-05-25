# simple_shell
This a project assigned in teams for alx Students cohort 13. 
DESCRIPTION: A simple shell which is identical to the sh in linux.

Our shell program is a command-line interpreter that takes user input commands
with multiple arguments and executes them. There is an ineractive mode and a
non-interactive mode. When a command is executed, a child process
is created to perform the command. Once the child process is killed, the command
line will be ready again to take in user input.

Accepts builtin commands: exit, help, and env.
Handles basic commands stored in the PATH.
Executes by forking a child process.

## Testing
To test, after cloning this repository, use the following to compile the program.
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

When you run ./hsh you will see a prompt represented by the dollar sign '$' ready
for your command. 
Or for non-interactive mode, after compiling, you can use the following to list
the items in the directory (for example).
echo "/bin/ls" | ./hsh



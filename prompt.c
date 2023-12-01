#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COMMAND 1024

void prompt(char **av, char **env)
{
	char *string = NULL;
	int i, j, status;
	size_t n = 0;
	ssize_t num_char;
	char *argv[MAX_COMMAND];
	pid_t child_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		num_char = getline(&string, &n, stdin);
		if (num_char == -1 || num_char == EOF)
		{
			free(string);
			break;
		}
		i = 0;
		while (string[i])
		{
			if (string[i] == '\n')
				string[i] = 0;
			i++;
		}
		j = 0;
		argv[j] = strtok(string, " ");
		while (argv[j])
		{
			argv[++j] = strtok(NULL, " ");
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
			}
		}
		else
		{
			wait(&status);
		}
	};
}

int main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		prompt(av, env);
	}
}

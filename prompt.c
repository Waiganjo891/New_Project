#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COMMAND 1024

void prompt(char **av, char **env)
{
	char *line = NULL;
	int i, a, j, status;
	size_t len = 0;
	ssize_t read;
	char *argv[MAX_COMMAND];
	pid_t child_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (line[i])
		{
			if (line[i] == '\n')
				line[i] = 0;
			i++;
		}
		if (strcmp(line, "exit") == 0)
		{
			break;
		}
		else if (strcmp(line, "env") == 0)
		{
			a = 0;
			while (env[a] != NULL)
			{
				printf("%s\n", env[a]);
				a++;
			}
			continue;
		}
		j = 0;
		argv[j] = strtok(line, " ");
		while (argv[j])
		{
			argv[++j] = strtok(NULL, " ");
		}
		if (access(argv[0], X_OK) == -1)
		{
			printf("%s: No such file or directory\n", argv[0]);
			continue;
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			free(line);
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
	}
}

int main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		prompt(av, env);
	}
	return (0);
}

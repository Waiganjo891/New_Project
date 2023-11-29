#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *word;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1 || read == EOF)
		{
			break;
		}

		word = strtok(line, " ");
		if (word != NULL)
		{
			word[strcspn(word, "\n")] = '\0';
			char *argv[] = {word, NULL};

			if (execve(word, argv, environ) == -1)
			{
				perror("execve");
			}
		}
	}
	free(line);
	return (0);
}

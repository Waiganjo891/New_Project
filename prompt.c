#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
		while (word != NULL)
		{
			printf("%s\n", word);
			word = strtok(NULL, " ");
		}
	}
	free(line);
	return (0);
}

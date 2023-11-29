#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *buffer;
	size_t bufsize = 1024;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	printf("$ ");
	getline(&buffer, &bufsize, stdin);
	buffer[strcspn(buffer, "\n")] = 0;
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}

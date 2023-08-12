#include "main.h"

int main(int ac, char **av, char **en)
{
	char *lineptr = NULL, *token, *cpy_lineptr, *fullpath;
	size_t n = 0, length;
	char *delim = " \n";
	pid_t pid;
	char **argv;
	int status = 0, i;
	int counter = 0;


	while (1)
	{
		printf("#cisfun$ ");
		length = getline(&lineptr, &n, stdin);

		if (length == -1)
		{
			perror("null input");
			free(lineptr);
			exit(1);
		}
		cpy_lineptr = strdup(lineptr);
		if (cpy_lineptr == NULL)
			perror("strdup fail");

		token = strtok(cpy_lineptr, delim);
		 while (token != NULL)
		 {
			 counter++;
			 token = strtok(NULL, delim);
		 }

		argv = malloc(sizeof(char *) * (counter + 1));
		if (argv == NULL)
		{
			free(lineptr);
			free(argv);
			perror("malloc fail at argv in shell.c");
			exit(1);
		}

		i = 0;
		token = strtok(lineptr, delim);
		while (token != NULL)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		fullpath = pathname(en, lineptr, delim);
		if (fullpath == NULL)
		{
			perror("full path is null");
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			execve(fullpath, argv, en);
			perror("execve regarding fullpath");
		}
		else
		{
			wait(NULL);
		}

		free(argv);

	}

	free(lineptr);
	return (0);

}

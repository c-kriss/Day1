// shell.c
#include "main.h"

int main(int ac, char **av, char **en)
{
    en = environ;
    char *lineptr = NULL, *fullpath;
    size_t n = 0, length;
    char *delim = " \n";
    pid_t pid;
    char **argv;

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

        char *cpy_lineptr = strdup(lineptr);
        if (cpy_lineptr == NULL)
        {
            perror("strdup fail");
            free(lineptr);
            exit(1);
        }

        int counter = 0;
        char *token = strtok(cpy_lineptr, delim);
        while (token != NULL)
        {
            counter++;
            token = strtok(NULL, delim);
        }

        argv = malloc(sizeof(char *) * (counter + 1));
        if (argv == NULL)
        {
            perror("malloc fail at argv in shell.c");
            free(lineptr);
            free(cpy_lineptr);
            exit(1);
        }

        int i = 0;
        token = strtok(lineptr, delim);
        while (token != NULL)
        {
            argv[i] = token;
            i++;
            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        fullpath = pathname(en, argv[0], delim);
        if (fullpath == NULL)
        {
            fprintf(stderr, "Command not found or error.\n");
            free(argv);
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

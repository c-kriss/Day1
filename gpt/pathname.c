// pathname.c
#include "main.h"

char *pathname(char **en, char *command, char *delim)
{
    char *value, *token;
    char *combine;
    int i, found = 0;
    int access_value;
    char *path = "PATH=";
    char *delim2 = ":";
    size_t length;

    if (command == NULL)
        return NULL;

    for (i = 0; en[i]; i++)
    {
        if (strncmp(en[i], path, strlen(path)) == 0)
        {
            value = en[i] + strlen(path);
            token = strtok(value, delim2);

            while (token != NULL)
            {
                length = strlen(token) + strlen(command) + 2;
                combine = malloc(length);

                if (combine == NULL)
                    return NULL;

                strcpy(combine, token);
                strcat(combine, "/");
                strcat(combine, command);

                access_value = access(combine, X_OK);
                if (access_value == 0)
                {
                    found = 1;
                    break;
                }

                free(combine);
                token = strtok(NULL, delim2);
            }

            if (found)
                break;
        }
    }

    if (!found)
        return NULL;

    return combine;
}

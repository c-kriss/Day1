#include "main.h"

char *pathname(char **en, char *lineptr, char *delim)
{
	char *value, *token;
	size_t length;
	char *combine = "";
	int i, found = 0;
	int access_value;
	char *path = "PATH=";
	char *delim2 = ":";
	char *token2 = strtok(lineptr, delim);

	if (lineptr == NULL)
		return (NULL);

	for (i = 0; en[i] != NULL; i++)
	{
		if (strstr(en[i], path) == en[i])
		{
			value = en[i] + strlen(path);
			token = strtok(value, delim2);

			while (token != NULL)
			{

				length  = strlen(token) + strlen(token2) + 2;
				combine = malloc(sizeof(char) * length);

				if (combine == NULL)
					return (NULL);

				strcpy(combine, token);
				strcat(combine, "/");
				strcat(combine, token2);
				access_value = access(combine, X_OK);
				if (access_value == 0)
				{
					found = 1;
					break;
				}
					free(combine);
					token = strtok(NULL, delim2);
			}

			if(found)
				break;
		}
	}

	if(!found)
		return (NULL);

	return (combine);
}

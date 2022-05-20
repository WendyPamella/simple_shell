#include "mainshell.h"

/**
 * create_env - lists all environmnet varaibles
 * @env: array of all environment variables
 * env_list: lists all environment variables
 *
 * Return: new lis, else return NULL
 */

char *_getenv(list_t *env_list, char *name)
{
	list_t *trav = env_list;

	if (name == NULL)
	{
		return (NULL);
	}

	while (trav && _strcmp(trav->name, name))  /* check each node for a match */
	{
		trav = trav->next;
	}

	if (trav)
		return (trav->value);

	return (NULL);
}

int _setenv(list_t *env_list, const char *name, const char *value, int ow)
{
	int index;

	if (name == NULL || value == NULL || is_in_str(name, '='))
		return (-1);

	/* find index of node with name */
	index = find_name(env_list, name);

	/* if name not in list */
	if (index == -1)
	{
		if (add_node_end(&env_list, name, value) == NULL)
			return (-1);

		return (0);
	}
int _unsetenv(list_t *env_list, const char *name)
{
	int index;

	if (name == NULL)
		return (-1);

	/* find index of node to delete */
	index = find_name(env_list, name);

	/* if name is not in the list */
	if (index == -1)
		return (0);

	/* delete node at index */
	if (delete_node_index(&env_list, index) == -1)
		return (-1);

	return (0);
}

if (ow)
		return (update_value(env_list, index, value));

	return (0);
}

void print_env(list_t *env_list)
{
	list_t *trav = env_list;

	while (trav != NULL)
	{
		/*printf("[%d] ", trav->index);*/
		/*printf("%s=%s\n", trav->name, trav->value);*/

		write(STDOUT_FILENO, trav->name, _strlen(trav->name) + 1);
		write(STDOUT_FILENO, "=", 2);
		write(STDOUT_FILENO, trav->value, _strlen(trav->value) + 1);
		write(STDOUT_FILENO, "\n", 2);

		trav = trav->next;
	}
}

list_t *create_env(char **env, list_t *env_list)
{
	unsigned int i;
	char *name, *value;

	if (env == NULL)
	{
		return (NULL);
	}

	for (i = 0; env[i]; i++)
	{
		name = _strtok(env[i], "=");
		value = _strtok(NULL, "\n");

		if (add_node_end(&env_list, name, value) == NULL)
		{
			return (NULL);
		}
	}

	return (env_list);
}


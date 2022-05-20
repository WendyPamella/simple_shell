#include "mainshell.h"

/**
 * get_built - checks for built-in commands
 * excutes asssociated functions
 * @input_list: represents input command
 * @shell_name: program name
 * @env-list: environment variables
 *
 * Return: always an integer, unless it's not existing then return -1
 */

int exit_shell(list_t *input_list, char *shell_name, list_t **env_list_ptr)
{
	int num;
	char *error_message[4];

	error_message_init(error_message, shell_name, input_list->name);

	if (input_list->next == NULL)
		return (0);

	num = _atoi(input_list->next->name);

	if (num == -1)
	{
		error_message[2] = "Illegal number";
		error_message[3] = input_list->next->name;
		print_error(error_message);
		return (-2);
	}

	(void)env_list_ptr;
	return (num);
}

int unsetenv_func(list_t *input_list, char *shell_name, list_t **env_list_ptr)
{
	char *name;
	char *error_message[4];

	error_message_init(error_message, shell_name, input_list->name);

	if (input_list->next == NULL)
	{
		error_message[2] = "invalid number of arguments";
		print_error(error_message);
		return (-2);
	}

	name = input_list->next->name;

	if (_unsetenv(*env_list_ptr, name) == -1)
	{
		error_message[2] = "error";
		print_error(error_message);
	}

	return (-2);
}
int env_func(list_t *input_list, char *shell_name, list_t **env_list_ptr)
{
	print_env(*env_list_ptr);

	(void)input_list;
	(void)shell_name;
	return (-2);
}

int get_built(list_t *input_list, char *shell_name, list_t *env_list)
{
	char *name;
	int i;

	built_s built_ins[] = {
		{"exit", exit_shell},
		{"env", env_func},
		{"setenv", setenv_func},
		{"unsetenv", unsetenv_func},
		{NULL, NULL}
	};

	name = input_list->name;

	for (i = 0; built_ins[i].name; i++)
	{
		if (_strcmp(name, built_ins[i].name) == 0)
			return (built_ins[i].f(input_list, shell_name, &env_list));
	}

	return (-1);
}

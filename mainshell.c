#include "mainshell.h"

/**
 * main - simple shell is implemented
 *
 * @ac: no of command lines
 * @av: array of commandline arguments
 * @env: array of all environment variables
 *
 * Return: 0 if successful, 1 if not
 */

int main(int ac, char **av, char **env)
{
	list_t *env_list = NULL;
	int shell_return;

	env_list = create_env(env, env_list);

	signal(SIGINT, sig_handler);

	shell_return = shell(env_list, av[0]);

	if (shell_return)
	{
		free_list(env_list);
		exit(shell_return);
	}

	(void)ac;

	free_list(env_list);

	return (0);
}

void sig_handler(int sig)
{
	signal(sig, sig_handler);
	write(STDOUT_FILENO, "\n", 2);
	prompt();
}

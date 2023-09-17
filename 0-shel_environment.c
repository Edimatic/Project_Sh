#include "function.h"

/**
 * _myenv - prints the current environment
 *
 * @update: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0 after execution
 */
int _myenv(update_p *update)
{

/* Print the environment list using the print_list_str function */
	print_list_str(update->env);
	return (0);
}

/**
 * *_getenv - Collect the value of an environ variable.
 *
 * @update: Structure containing potential arguments. Used to maintain
 * @label: Environment variable name given.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(update_p *update, const char *label)
{
	list_t *node = update->env;
	char *b;

	while (node)
	{
/* Check if the node's string starts with the given name */
		b = begin_on(node->str, label);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new envt variable,if not modify the current one.
 *
 * @update: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0 after execution
 */
int _mysetenv(update_p *update)
{
	if (update->argc != 3)
	{
		_funcputs("Incorrect number of arguements\n");
		return (1);
	}

	/* Set or modify the environment variable using the _setenv function */
	if (_setenv(update, update->argv[1], update->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Take out an environment variable.
 *
 * @update: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0 after execution.
 */
int _myunsetenv(update_p *update)
{
	int v;

	if (update->argc == 1)
	{
		_funcputs("Too few arguements.\n");
		return (1);
	}
/* Loop through provided arguments and unset environment variables */
	for (v = 1; v <= update->argc; v++)
		_unsetenv(update, update->argv[v]);

	return (0);
}

/**
 * populate_env_list - populates envt linked list of the file.
 *
 * @update: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0 after execution.
 */
int populate_env_list(update_p *update)
{
	list_t *node = NULL;
	size_t m;

	/* Populate the environment linked list using the environ array */
	for (m = 0; environ[m]; m++)
		add_node_end(&node, environ[m], 0);
	update->env = node;
	return (0);
}


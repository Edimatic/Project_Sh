#include "function.h"

/**
 * get_environ - Returns the actual copy of environment string array
 *
 * @update: Structure containing potential arguments. Used to maintain
 *          constant prototype.
 *
 * Return: Pointer to the array of environment strings.
 */
char **get_environ(update_p *update)
{
if (!update->environ || update->env_changed)
	{

/* Convert linked list to string array */
	update->environ = list_to_strings(update->env);
	update->env_changed = 0;
	}

	return (update->environ);
}

/**
 * _unsetenv - Remove an environment variable
 *
 * @update: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @varia: The string representing the environment variable
 *
 *  Return: 1 on successful delete, 0 otherwise
 */
int _unsetenv(update_p *update, char *varia)
{
	list_t *node = update->env;
	size_t q = 0;
	char *pik;

	if (!node || !varia)
		return (0);

	while (node)
	{
		pik = begin_on(node->str, varia);
		if (pik && *pik == '=')
		{
		update->env_changed = delete_node_at_index(&(update->env), q);
			q = 0;
			node = update->env;
			continue;
		}
		node = node->next;
		q++;
	}
	return (update->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @update: Structure containing potential arguments. Used to maintain
 *        constant prototype.
 * @varia: The string representing the environment variable.
 * @va: The string representing the environment variable's value.
 *
 *  Return: Always 0 after execution
 */
int _setenv(update_p *update, char *varia, char *va)
{
	char *bufa = NULL;
	list_t *node;
	char *pik;

	if (!varia || !va)
		return (0);
/* Allocate memory for var=value pair */
	bufa = malloc(_strlen_(varia) + _strlen_(va) + 2);
	if (!bufa)
		return (1);
	_strcpy_(bufa, varia);/* Copy variable name to buffer */
	_strcat_(bufa, "=");/* Append '=' */
	_strcat_(bufa, va);/* Append value */
	node = update->env;

/* Check if variable exists; if yes, update its value; if not, add new entry */
	while (node)
	{
		pik = begin_on(node->str, varia);
		if (pik && *pik == '=')
		{
			free(node->str);
			node->str = bufa;
			update->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(update->env), bufa, 0);/* Add new entry to linked list */
	free(bufa);
	update->env_changed = 1;
	return (0);
}

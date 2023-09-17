#include "function.h"

/**
 * _prohistory_ - displays the history list, one command per line, preceded
 *              by line numbers, starting which is at 0.
 *
 *@update: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0 at the end of execution
 */
int _prohistory_(update_p *update)
{
	/*Display the history list using the print_list function */
	print_list(update->history);
	return (0);
}

/**
 * unmake_alias_ - Unsets an alias by deleting it from the alias linked list.
 *
 * @update: Parameter struct containing relevant data.
 * @str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error after execution
 */
int unmake_alias_(update_p *update, char *str)
{
	char *b;
	char w;
	int ret;

/* Find the equal sign in the alias string */
	b = _strchr_(str, '=');
	if (!b)
		return (1);

/* Temporarily replace the equal sign with null terminator */
	w = *b;
	*b = 0;

/* Delete the alias node from the linked list */
	ret = delete_node_at_index(&(update->alias),
	get_node_index(update->alias, node_starts_with(update->alias, str, -1)));

/* Restore the equal sign */
	*b = w;
	return (ret);
}

/**
 * make_alias_ - Sets an alias by adding it to the alias linked list.
 *
 * @update: Parameter struct containing relevant data.
 * @str: The string alias to set.
 *
 * Return: Always 0 on success, 1 on error after execution
 */
int make_alias_(update_p *update, char *str)
{
	char *b;

/* Find the equal sign in the alias string */
	b = _strchr_(str, '=');
	if (!b)
		return (1);

/* If alias value is empty, unset the alias */
	if (!*++b)
		return (unmake_alias_(update, str));

/* Unset existing alias and add new alias to linked list */
	unmake_alias_(update, str);
	return (add_node_end(&(update->alias), str, 0) == NULL);
}

/**
 * show_alias_ - Prints an alias string in the format 'alias'='value'.
 *
 * @node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error
 */
int show_alias_(list_t *node)
{
	char *b = NULL, *v = NULL;

	if (node)
	{
/* Find the equal sign in the alias node's string */
		b = _strchr_(node->str, '=');

/* Print the alias name followed by '=' and enclosed value in single quotes*/
		for (v = node->str; v <= b; v++)
		_putchar(*v);
		_putchar('\'');
		_puts_(b + 1);
		_puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * _proalias_ - Mimics the alias builtin (man alias).
 *
 * @update: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *  Return: Always 0 after execution
 */
int _proalias_(update_p *update)
{
	int m = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (update->argc == 1)
	{
/* If no arguments provided, print all aliases */
		node = update->alias;
		while (node)
		{
			show_alias_(node);
			node = node->next;
		}
		return (0);
	}

/* Loop through provided arguments to set or print aliases */
	for (m = 1; update->argv[m]; m++)
	{
		b = _strchr_(update->argv[m], '=');
		if (b)
			make_alias_(update, update->argv[m]);
		else
		show_alias_(node_starts_with(update->alias, update->argv[m], '='));
	}

	return (0);
}


#include "function.h"

/**
 * remove_update - Initializes an update_p structure by resetting its fields.
 *
 * @update: Pointer to the update_p struct to be cleared.
 */
void remove_update(update_p *update)
{
	update->arg = NULL;
	update->argv = NULL;
	update->path = NULL;
	update->argc = 0;
}

/**
 * make_update - Initializes an update_p structure with provided arguments.
 *
 * @update: Pointer to the update_p struct to be initialized.
 * @him: Argument vector (array of strings).
 */
void make_update(update_p *update, char **him)
{
	int g = 0;

	update->fname = him[0];/* Set the program's filename */
	if (update->arg)
	{
	update->argv = strtop_k(update->arg, " \t");/* Tokenize argument string */
			if (!update->argv)
		{
	/* Allocate space for argv array */
			update->argv = malloc(sizeof(char *) * 2);
	if (update->argv)
			{
	update->argv[0] = _strdup_(update->arg);/* Copy argument to argv */
				update->argv[1] = NULL;
			}
		}
		for (g = 0; update->argv && update->argv[g]; g++)/* Count argc */
			;
		update->argc = g;

		replace_alias(update);/* Replace aliases in argv */
		replace_vars(update);/* Replace environment variable references in argv */
	}
}

/**
 * discharge_update - Frees memory associated with an update_p struct's fields.
 *
 * @update: Pointer to the info_t struct to be freed.
 *
 * @hal: Flag indicating if all fields should be freed.
 */
void discharge_update(update_p *update, int hal)
{
	ffree(update->argv);/* Free the argv array */
	update->argv = NULL;
	update->path = NULL;
	if (hal)
	{
		if (!update->cmd_buf)
	/* Free argument string if not part of a command chain */
			free(update->arg);
		if (update->env)
			free_list(&(update->env));/* Free environment linked list */
		if (update->history)
			free_list(&(update->history));/* Free history linked list */
		if (update->alias)
			free_list(&(update->alias));/* Free alias linked list */
		ffree(update->environ);/* Free environment string array */
			update->environ = NULL;
		bfree((void **)update->cmd_buf);/* Free command buffer */
		if (update->readfd > 2)
			close(update->readfd);/* Close file descriptor */
		_putchar(BUF_FLUSH);/* Flush the output buffer */
	}
}

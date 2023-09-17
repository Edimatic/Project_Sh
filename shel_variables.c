#include "function.h"

/**
 * is_chain - Test if the current char in the buffer is a chaining delimiter.
 *
 * @update: The parameter structure.
 * @bofa: The character buffer.
 * @shw: Address of the current position in bufa.
 *
 * Return: 1 if a chaining delimeter, 0 otherwise.
 */
int is_chain(update_p *update, char *bofa, size_t *shw)
{
	size_t h = *shw;

	if (bofa[h] == '|' && bofa[h + 1] == '|')/* Check for '||' */
	{
		bofa[h] = 0;
		h++;
		update->cmd_buf_type = CMD_OR;
	}
	else if (bofa[h] == '&' && bofa[h + 1] == '&')/* Check for '&&' */
	{
		bofa[h] = 0;
		h++;
		update->cmd_buf_type = CMD_AND;
	}
	else if (bofa[h] == ';') /* Seen the last command */
	{
		bofa[h] = 0; /* Reallocate semicolon with null */
		update->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*shw = h;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 *
 * @update: The parameter structure
 * @bof: The char buffer
 * @sh: Address of current position in bufa.
 * @v: Starting position in bufa.
 * @dis: Length of bufa.
 *
 * Return: Void after execution.
 */
void check_chain(update_p *update, char *bof, size_t *sh, size_t v, size_t dis)
{
	size_t pin = *sh;

	if (update->cmd_buf_type == CMD_AND)
	{
		if (update->status)
		{
			bof[v] = 0;
			pin = dis;
		}
	}
	if (update->cmd_buf_type == CMD_OR)
	{
		if (!update->status)
		{
			bof[v] = 0;
			pin = dis;
		}
	}

	*sh = pin;
}

/**
 * replace_alias - Replaces an aliases in the tokenized string.
 *
 * @update: The parameter structure to the program
 *
 * Return: 1 if replaced, 0 otherwise after execution.
 */
int replace_alias(update_p *update)
{
	int kim;
	list_t *node;
	char *ok;

	for (kim = 0; kim < 10; kim++)
	{
		node = node_starts_with(update->alias, update->argv[0], '=');
		if (!node)
			return (0);
		free(update->argv[0]);
		ok = _strchr_(node->str, '=');
		if (!ok)
			return (0);
		ok = _strdup_(ok + 1);
		if (!ok)
			return (0);
		update->argv[0] = ok;
	}
	return (1);
}

/**
 * replace_vars - Replace variables in the tokenized string.
 *
 * @update: The parameter structure.
 *
 * Return: 1 if replaced, 0 otherwise after execution.
 */
int replace_vars(update_p *update)
{
	int kim = 0;
	list_t *node;

	for (kim = 0; update->argv[kim]; kim++)
	{
		if (update->argv[kim][0] != '$' || !update->argv[kim][1])
			continue;

		if (!_strcmp_(update->argv[kim], "$?"))
		{
			replace_string(&(update->argv[kim]),
					_strdup_(change_numz(update->status, 10, 0)));
			continue;
		}
		if (!_strcmp_(update->argv[kim], "$$"))
		{
			replace_string(&(update->argv[kim]),
					_strdup_(change_numz(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(update->env, &update->argv[kim][1], '=');
		if (node)
		{
			replace_string(&(update->argv[kim]),
					_strdup_(_strchr_(node->str, '=') + 1));
			continue;
		}
		replace_string(&update->argv[kim], _strdup_(""));

	}
	return (0);
}

/**
 * replace_string - Replacing a string is allow.
 *
 * @mature: Address of the mature string.
 * @latest: latest string
 *
 * Return: 1 if replaced, 0 otherwise after execution.
 */
int replace_string(char **mature, char *latest)
{
	free(*mature);
	*mature = latest;
	return (1);
}


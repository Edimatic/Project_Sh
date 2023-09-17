#include "function.h"

/**
 * hsh - Main shell loop.
 *
 * @update: Pointer to the parameter & return update struct.
 * @agtv: Argument vector from main()source.
 *
 * This function is the main loop of the shell. It repeatedly clears the
 * update structure, prompts the user for input if interactive, gets input,
 * sets update based on the input, checks for built-in commands, and if not
 * found, looks for and executes external commands.
 *
 * Return: 0 on success, 1 on error, or error code at the end.
 */
int hsh(update_p *update, char **agtv)
{
	ssize_t read_status = 0;/* Status of input reading */
	int builtin_ret = 0;/*Return value of built-in commands*/

	while (read_status != -1 && builtin_ret != -2)
	{
		remove_update(update);
		if (opt_conjoint(update))
			_puts_("$ ");
		_funcputchar(BUF_FLUSH);
		read_status = wax_input(update);
		if (read_status != -1)
		{
			make_update(update, agtv);
			builtin_ret = asset_builtin(update);
			if (builtin_ret == -1)
				asset_cmd(update);
		}
		else if (opt_conjoint(update))
			_putchar('\n');
		discharge_update(update, 0);
	}
	write_history(update);
	discharge_update(update, 1);
	if (!opt_conjoint(update) && update->status)
		exit(update->status);
	if (builtin_ret == -2)
	{
		if (update->err_num == -1)
			exit(update->status);
		exit(update->err_num);
	}
	return (builtin_ret);
}

/**
 * asset_builtin - Bring out the builtin command.
 *
 * @update: Pointer to the parameter & return update structure.
 *
 * This function searches for a builtin command within the provided update
 * structure and executes it if found. If not found, it returns -1.
 *
 * Return: -1 if builtin not found, 0 if builtin executed successfully,
 *	1 if builtin found but not successful, 2 if builtin signals exit()
 */
int asset_builtin(update_p *update)
{
	int read_status;
	int builtin_pro = -1;
	builtin_submit builtinsbt[] = {
		{"exit", _proexit},
		{"env", _myenv},
		{"help", _prohelp},
		{"history", _prohistory_},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _procd},
		{"alias", _proalias_},
		{NULL, NULL}
	};

	for (read_status = 0; builtinsbt[read_status].type; read_status++)
		if (_strcmp_(update->argv[0], builtinsbt[read_status].type) == 0)
		{
			update->line_count++;
			builtin_pro = builtinsbt[read_status].func(update);
			break;
		}
	return (builtin_pro);
}

/**
 * asset_cmd - Finds a command in PATH
 *
 * @update: Pointer to the parameter & return info structure.
 *
 * This function looks for an external command within the PATH environment
 * variable. If found, it sets the path and executes the command.
 *
 * Return: void after execution.
 */
void asset_cmd(update_p *update)
{
	char *direction = NULL;
	int y;
	int k;

	update->path = update->argv[0];
	if (update->linecount_flag == 1)
	{
		update->line_count++;
		update->linecount_flag = 0;
	}
	for (y = 0, k = 0; update->arg[y]; y++)
		if (!opt_deli(update->arg[y], " \t\n"))
			k++;
	if (!k)
		return;

	direction = asset_path(update, _getenv(update, "PATH="), update->argv[0]);
	if (direction)
	{
		update->path = direction;
		fork_cmd(update);
	}
	else
	{
		if ((opt_conjoint(update) || _getenv(update, "PATH=")
					|| update->argv[0][0] == '/') && mult_cmd(update, update->argv[0]))
			fork_cmd(update);
		else if (*(update->arg) != '\n')
		{
			update->status = 127;
			show_error(update, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run a command.
 *
 * @update: Pointer to the parameter & return info structure.
 *
 * Return: void aftrer execution.
 */
void fork_cmd(update_p *update)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: Handle Errors at this point */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(update->path, update->argv, get_environ(update)) == -1)
		{
			discharge_update(update, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(update->status));
		if (WIFEXITED(update->status))
		{
			update->status = WEXITSTATUS(update->status);
			if (update->status == 126)
				show_error(update, "Permission denied\n");
		}
	}
}

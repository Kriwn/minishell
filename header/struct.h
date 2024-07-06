#ifndef STRUCH_H
# define STRUCH_H

typedef struct tuple
{
	char		*key;
	char		*value;
	struct	tuple *next;
	struct	tuple *tail;
} t_tuple;


typedef struct p_pipe
{
	int		*process_pid;
	int		status_pid;
	char	**env;
	char	**path;
	char	*cmd;
	int		fd_in;
	int		fd_out;
}	t_p;

typedef struct	e_env
{
	t_tuple	*tuple;
	char	**env;
	char	*home_path;
	int		code;
	char	*cur_path;
	char	*cur_input;
	int		count;
}	t_env;

#endif

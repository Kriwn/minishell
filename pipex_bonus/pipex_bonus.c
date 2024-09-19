/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:12:29 by krwongwa          #+#    #+#             */
/*   Updated: 2024/04/19 13:59:54 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent_process(t_p *list)
{
	if (list->infile > -1)
		close(list->infile);
	list->infile = dup(list->pipe[0]);
	close(list->pipe[0]);
	list->count += 1;
	close(list->pipe[1]);
}

void	child_process(char **argv, char **env, t_p *list)
{
	if (list->count == 0)
		open_in_file(argv[1], list);
	if (list->count == list->argc - 4)
	{
		if (list->here_doc)
			open_out_file(argv[list->argc -1], list, 0);
		else
			open_out_file(argv[list->argc -1], list, 1);
	}
	else
		pipe_write(list);
	run_cmd(argv[list->count + 2], env, list->infile, list);
}

int	wait_all_process(t_p *list)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < list->argc - 3)
	{
		if (list->process_pid[i] > -1)
			waitpid(list->process_pid[i], &status, WUNTRACED);
		i++;
	}
	freelist(list);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	t_p	*list;
	int	status;

	list = malloc(sizeof(t_p));
	init(list, argc);
	if (argc <= 4)
		ft_puterror("Input wrong argument", 22, list);
	if (check(argv[1], "here_doc"))
		list->here_doc = do_here_doc(argv[2], list);
	while (list->count < argc - 3)
	{
		if (pipe(list->pipe) == -1)
			ft_puterror("Pipe error", errno, list);
		list->process_pid[list->count] = fork();
		if (list->process_pid[list->count] == -1)
			ft_puterror("Fork error", errno, list);
		if (list->process_pid[list->count] == 0)
			child_process(argv, env, list);
		else if (list->process_pid[list->count] > 0)
			parent_process(list);
	}
	return (wait_all_process(list));
}

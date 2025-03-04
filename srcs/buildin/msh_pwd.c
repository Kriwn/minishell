/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krwongwa <krwongwa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:08:30 by krwongwa          #+#    #+#             */
/*   Updated: 2025/01/15 23:02:46 by krwongwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy(const char *s)
{
	size_t	i;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	i = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_getcwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	return (path);
}

int	msh_pwd(t_p *list)
{
	char	*current_path;
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	current_path = copy(get_value_from_key(list->msh->tuple,"PWD"));
	if(!current_path)
		current_path = ft_getcwd();
	handle_fd(list);
	ft_putendl_fd(current_path, STDOUT_FILENO);
	if (list->fd_out != 1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (current_path)
		free(current_path);
	return (EXIT_SUCCESS);
}

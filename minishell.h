/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:58:09 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/04/04 16:16:37 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_PIPES 1024
typedef struct s_data
{
	char **env;
	int cmd_nbrs;	
	int i;
}	t_data;

typedef struct s_lexer
{
	int position;
	int lenght;
	char *input;
}	t_lexer;

typedef struct s_token
{
	char **args;
	struct s_token *next;
}	t_token;


char	**ft_split(char const *s, char c);
char *check_path(char **env, char *cmd);
void	create_child(t_data *data, int pipe_fd[][2], char *input);
void create_pipe(t_data *data, int pipe_fd[][2]);
void	close_pipes(t_data *data, int pipe_fd[][2]);
void child(t_data *data, int pipe_fd[][2], char *input);
void	execute_cmd(t_data *data, char *input);
void first_cmd(t_data *data, int pipe_fd[][2]);
void middle_cmd(t_data *data, int pipe_fd[][2]);
void last_cmd(t_data *data, int pipe_fd[][2]);
void	wait_children(t_data *data, int *status);
void write_split(char **split);

#endif
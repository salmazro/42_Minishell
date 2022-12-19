/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:56:40 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <errno.h>
# include "ft_printf.h"
# include "libft.h"

# define SYMBOLS "|><"
# define SPACES " \t\r\n\f\v"
# define QUOTES "\'\""

typedef enum e_cmdtype
{
	EXEC = 0,
	REDIR = 1,
	PIPE = 2,
}	t_cmdtype;

typedef struct s_kms
{
	char	*key;
	char	*val;
}	t_kms;

typedef struct s_env
{
	t_list	*kms;
	char	**env;
}	t_env;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execmd
{
	int		type;
	char	**argv;
	t_env	*env;
}	t_execmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*subcmd;
	int		mode;
	int		fd;
	char	*file;
}	t_redircmd;

typedef struct s_appinfo
{
	t_cmd		*cmd;
	t_env		*env;
	int			exit_status;
	int			pipe_out;
	int			pipe_in;
	char		*delim;
}	t_appinfo;

extern t_appinfo	g_appinfo;

void	print_error(char *s);

int		getcmd(char *prefix, char **buf);

pid_t	ft_fork(void);

t_env	*init_env(char **env);

char	**ft_getenv(t_list *lst);

void	update_env(t_env *env);

char	*merge_keymap(t_kms *km);

void	update_keymap(t_kms *km, char *keyvalue);

t_list	*find_keymap_key(t_list *lst, char *keyvalue);

void	add_keymap(t_list **lst, char *keyvalue, int addonly);

void	remove_keymap(t_list **lst, char *key);

char	*ft_first_word(char *str);

void	ft_remove_char(char *str, char c);

char	*ft_strljoin(char *s1, char *s2, int n);

void	ft_clearsplit(char **str);

size_t	ft_strclen(char *s, char c);

char	*ft_strldup(char *src, int size);

size_t	ft_strdlen(char **s);

int		ft_strequals(char *s1, char *s2);

int		ft_strcontains(char *s1, char *s2);

void	clear_keymap(void *content);

void	clear_env(t_env *env);

void	print_export(t_list *lst);

void	print_env(t_list *lst);

void	print_keymaps(t_list *lst);

void	print_strsplit(char **split);

t_list	*sort_keymap_alpha(t_list *lst);

void	exit_app(int status);

void	clear_cmd(t_cmd *cmd);

void	define_input_signals(void);

void	define_exec_signals(void);

void	ctrl_d(void);

void	ctrl_c(int sig);

void	sig_handler_heredoc(int sig_num);

void	update_exitstatus(void);

#endif

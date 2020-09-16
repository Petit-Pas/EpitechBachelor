/*
** minishell2.h for minishell2 in /home/angevil124/prog/PSU/PSU_2016_my_exec2
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Mar 18 09:24:37 2017 Benoit
** Last update Thu May  4 10:38:02 2017 Benoit Hoffman
*/

#ifndef			MINISHELL2_H_
# define		MINISHELL2_H_

typedef struct          s_command
{
  char                  *command;
  int                   previous_sep;
  int                   next_sep;
  struct s_command      *next;
}			t_command;

typedef struct		s_info
{
  int			should_exit;
  int			should_print_in;
  int			exit_value;
  t_command		*list;
  char			**tab;
  char			**tab2;
}			t_info;

typedef struct          s_pipe
{
  int                   default_entry;
  int                   default_exit;
  int			**pipes;
  int			*id;
  int			actual_old;
  int			count;
  int			to_close[2];
}                       t_pipe;

/*
** Parsing
*/

void			get_next(char *str, int *i, t_command *new);
void			get_previous(char *str, int *i, t_command *new);

int			my_parser(char *str, char ***env, t_info *info, int i);
int			is_a_separator(char c);

/*
** Execution
*/

void			parent(t_pipe *pipes, t_command *elem,
			       int id, t_info *info);
void			set_pipes(t_command *elem, t_pipe *pipes, t_info *info);
void			close_all(t_pipe *pipes);
void			wait_kids(t_pipe *pipes);
void			free_pipes(t_pipe *pipes);
void			manage_left(t_command *elem,
				    t_pipe *pipes,
				    char ***env, t_info *info);
void			manage_right(t_command *elem, t_pipe *pipes,
				     char ***env, t_info *info);
void			manage_basic(t_command *elem, t_pipe *pipes,
				     char ***env, t_info *info);

int			do_open(t_command *elem, t_pipe *pipes, char **argv);
int			do_left(t_command *elem, t_pipe *pipes,
				char **argv, int size);
int			do_lleft(t_pipe *pipes, char **argv);
int			manage_redir(t_command *list, char ***env,
				     t_info *info);
int			set_first_pipes(t_pipe *pipes, t_command *list, int i);

/*
** Tools
*/

void			swap(t_command *list);
void			free_list(t_command *tab);
void			my_putchar(char c, int exit);
void			double_free(char *str1, char *str2);
void			print_prompt(t_info *info);

int			match(char *str, char *str2);
int			do_env(char *str, char ***env, t_info *info);
int			free_tab(char **tab, int return_value);
int			my_strcmp(char *str, char *str2);
int			my_strlen(char *str);
int			my_putstr(char *str, int exit, int to_return);
int			count_argument(char *str, char separator);
int			count_purified(char *str, int i, int count);
int			count_argument(char *str, char separator);
int			free_and_return(char *str, int to_return);
int			get_argument_amount(char *str, char separator);
int			count_argument_pipe(char *str);
int			count_argument_quote(char *str, char separator);

char			*add_star(char *str);
char			*my_strdup(char *str);
char			*my_strcat(char *str1, char *str2,
				   int free1, int free2);
char			*is_in_path(char *str, char **my_env,
				    int i, int count);
char			*purify_str(char *str);
char			*remove_tab(char *str);
char			*get_next_line(int fd);
char			*wordtab_to_str(char **tab, int argc);

char			**copy_tab(char **tab);
char			**str_to_wordtab(char *str, int count, char separator);
char			**str_to_wordtab_pipe(char *str, int size);
char			**str_to_wordtab_quote(char *str, int size,
					       char separator);

/*
** Check
*/

void			check_status(int status, t_info *info);

int			is_mine(t_command *elem, char ***env,
				t_info *info, t_pipe *pipes);
int			my_check(char **commands);
int			check_quotes(char *str);
int			check_exists(char *str);
int			check_in_next(t_command *first);
int			is_in_directory(char *str, char *directory);
int			ambiguous_check(t_command *list);

char			*check_command_exists(char *str, char ***env);

/*
** Builtins
*/

int			do_cd(char *str, char ***env, t_info *info);
int			do_setenv(char *str, char ***env, t_info *info);
int			is_in_env(char *str, char **env);
int			do_unsetenv(char *str, char ***my_env, t_info *info);
int			manage_exit(char *str, char ***env, t_info *info);
int			check_setenv_validity(char **command);

char			*get_env_value(char *str, int var_length);

#endif			/* !MINISHELL2_H_ */

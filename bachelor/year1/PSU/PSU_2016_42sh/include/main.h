/*
** main.h for minishell2 in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Fri Mar 24 10:58:31 2017 Sahel Lucas--Saoudi
** Last update Sun May 21 10:32:39 2017 Sahel Lucas--Saoudi
*/

#ifndef MAIN_H_
# define MAIN_H_

typedef struct	s_shell
{
  char		**env;
  char		**path;
  char		**alias;
  char		**history;
  char		*command;
  char		*oldpwd;
  char		*pwd;
  char		*home;
  int		fd0;
  int		id_command;
  int		idmax;
  int		status;
  int		exit;
  int		sub;
}		t_shell;

char		**parse_(char *, char);
char		**set_var(char *, char *);
char		**create_env(char **);
char		**c_dico(int, ...);
char		**take_redir(char **, int);
char		**parse__redir(char *);
char		*getvar(char **, char *);
char		*epur(char *);
char		*add_str(char *, int, char *);
char		*add_char(char *, int, char *);
char		*add_and_free(char *, int, char *);
char		*getnextline_(int);
char		*without_before_(char *, char);
char		*only_before(char *, char);
char		*double_redir(char *);
char		*stralloc_(char *, char *);
int		put_minimalist(t_shell *);
int		set_path(char **, t_shell *);
int		validity(char **);
int		setnenv(char **, t_shell *);
int		is_valid(char *);
int		check_filename(char **);
int		howmany_(char *, char);
int		check_flexibility(t_shell *);
int		good_filename(char *, int *, int *);
int		good_file(char *);
void		free_tab(char **);
void		manage_command(t_shell *);
int		lexer(char **, t_shell *);
void		exec_manager(char **, t_shell *);
void		error_handling(int);
void		showtab_(char **);
int		exec_manage(char **, t_shell *);
int		exec_pipe_manager(char **, int, t_shell *);
void		setup_redir(char *, int *, char **);
void		reset01(int);
void		prompt(int);
void		close_(int);
int		end_manage(int *, char **, char **, char **);
int		check_file(char *, char);
char		**parse_and_or(char *);
int		check_next(int , char *);
int		*get_fd(char **, char **);
int		*command_loop(int *, char **, int, t_shell *);
int		check_exit_pipe(char **, int **, int *, t_shell *);
char		*cat_all(char *, char *);
int		check_access(const char *);
int		do_where(char *, int *, int *);
int		do_which(char *, int *, int *);
int		check_path_where(char *, t_shell *);
int		check_builtin_where(char *);
int		check_alias_where(char *, t_shell *);
int		check_path_which(char *, t_shell *);
int		check_builtin_which(char *);
int		check_alias_which(char *, t_shell *);
int		free_shell(t_shell *);
int		exit_return(t_shell *, int);
int		*exit_return_ptr(t_shell *, int *);
int		putstr_return(char *s, int out, int exit);

#endif /* !MAIN_H_ */

/*
** edit.h for  in /home/januar_m/delivery/PSU/edit_line
**
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
**
** Started on  Wed May 17 15:38:26 2017 Martin Januario
** Last update Fri May 19 14:07:18 2017 Benoit Hoffman
*/

#ifndef		EDIT_H_
# define	EDIT_H_

# include	<termios.h>
# include	"main.h"

typedef struct	s_key
{
    int		idx;
    int		input;
    int		cols;
    char	*key[10];
    t_shell	*shell;
}		t_key;

char		*loop_read(t_key *);
char		*reset_command(char *, int);
int             initial_checks(char **, struct s_key *,
                               struct termios *,
                               struct termios *);

/*
**		Protoypes of files sources.
*/

int		found_term(char **);
int		ini_keys(t_key *, char *);
int		check_is_key(t_key *, char *, char **);
void		key_left_(t_key *, char *, char **);
void		key_right_(t_key *, char *, char **);
void		key_top_(t_key *, char *, char **);
void		key_bottom_(t_key *, char *, char **);
void		key_sup_(t_key *, char *, char **);
void		key_del_(t_key *, char *, char **);
void		key_begin_(t_key *, char *, char **);
void		key_end_(t_key *, char *, char **);
void		key_sleft_(t_key *, char *, char **);
void		key_sright_(t_key *, char *, char **);
char		*move_line(char *, char *, t_key *);
void		get_input(t_shell *, t_key *);

/*
**		Protoypes of files basics.
*/

int		my_strlen(char *);
int		my_putstr(char *);
int		my_puterror(char *);

#endif		/* !EDIT_H_ */

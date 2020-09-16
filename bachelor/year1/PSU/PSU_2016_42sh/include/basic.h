/*
** basic.h for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:22:25 2017 Sahel Lucas--Saoudi
** Last update Fri May 19 07:49:39 2017 Benoit Hoffman
*/

#ifndef BASIC_H_
# define BASIC_H_

void    free_pipe(int **, int);
char	*strdup_(char *);
char	*strndup_(char *, int);
char	*strdupn_(char *, int);
char	*strcat_(char *);
char	*strcpy_(char *, char *);
char	*strncat_(char *, char *, int);
char	*strstr_(char *, char *);
int	strcmp_(char *, char *);
int	strncmp_(char *, char *, int);
int	strlen_(char *);
int	sp_len_(char *, int);
int	tablen_(char **);
int	power_(int, int);
int	sqrt_(int);
int	getnbr_(char *);
int	match(char *, char *);
int	is_prime(int);
void	putnbr_(int);
void	putchar_(char);
void	putstr_(char *, int);
void	puttab_(char **, int);
void	free_(char *);

#endif /* !BASIC_H_ */

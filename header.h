/*
** header.h for minishell in /home/champi_t/rendu/minishell1
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Mon Jan 11 20:53:37 2016 theo champion
** Last update Sun Jan 24 23:33:34 2016 theo champion
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#ifndef HEADER_H_
# define HEADER_H_
#endif /* !HEADER_H_ */

#ifndef READ_SIZE
# define READ_SIZE (2)
#endif /* !READ_SIZE */

typedef struct	s_control
{
  int		stop;
  int		*ptr_stop;
  int		readed;
}		t_control;

typedef struct	s_list
{
  char		*str;
  struct s_list	*next;
}		t_list;

char	*get_next_line(const int);
int	read_to_linebuf(char *, char **, char *, t_control *);
void	linebuf_to_offset(char *, char *, t_control *, int);
char	*offset_check(char *, char *);
int	my_strlen(char *);
void	my_putchar(char);
int	my_strcmp(char *, char *);
void	my_putstr(char *);
char	**my_str_to_wordtab(char *, int);
char	*put_in_tab(char *, int, int);
t_list  *add_elem_end(t_list *, char *);
t_list	*fill_list(char **);
t_list	*find_elem(t_list *, char *);
t_list	*del_elem(t_list *, t_list *);
char	**my_list_to_tab(t_list *, char **);
void	write_error(char *);
int	free_all(char **);
void	copy_environ(char ***, char **);
int	try_path(char *, char **, int);
void	my_env(t_list *);
t_list	*my_setenv(t_list *, char *, char *);
t_list	*my_unsetenv(t_list *, char **);
int	my_cd(char **, t_list *);
int	get_home(t_list *, char **);
char	*my_getenv(char **, char *);
t_list	*execute_builtin(char **, t_list *, int *);
int	path_validation(char *, char **);
int	fork_and_execute(char **, char **);
int	exe_system_cmd(char **env, char **cmd);

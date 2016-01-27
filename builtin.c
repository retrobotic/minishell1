/*
** builtin.c for minishell in /home/champi_t/rendu/minishell1
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Mon Jan 18 19:34:20 2016 theo champion
** Last update Sun Jan 24 22:49:17 2016 theo champion
*/

#include "header.h"

void		my_env(t_list *lenv)
{
  t_list	*tmp;

  tmp = lenv;
  while (tmp != NULL)
    {
      my_putstr(tmp->str);
      my_putchar('\n');
      tmp = tmp->next;
    }
}

t_list		*my_setenv(t_list *lenv, char *var, char *value)
{
  char		*new;
  t_list	*tochange;
  int		i;
  int		j;
  int		l_var;
  int		l_value;

  l_var = my_strlen(var);
  l_value = my_strlen(value);
  if ((tochange = find_elem(lenv, var)) != NULL)
    lenv = del_elem(lenv, tochange);
  if ((new = malloc(sizeof(char) * (l_var + l_value + 2))) == NULL)
    exit(1);
  i = 0;
  j = 0;
  while (var[i])
    new[i] = var[i++];
  new[i++] = '=';
  while (value[j])
    new[i++] = value[j++];
  new[i] = 0;
  lenv = add_elem_end(lenv, new);
  return (lenv);
}

t_list		*my_unsetenv(t_list *lenv, char **cmd)
{
  t_list	*todelete;

  if ((todelete = find_elem(lenv, cmd[1])) != NULL)
    lenv = del_elem(lenv, todelete);
  return (lenv);
}

int	my_cd(char **cmd, t_list *lenv)
{
  char	buf[200];
  char	*home;

  my_setenv(lenv, "OLDPWD", getcwd(buf, 200));
  if (!cmd[1])
    {
      get_home(lenv, &home);
      if (chdir(home) != 0)
        {
          write_error("No such file or directory.\n");
          return (1);
        }
    }
  else
    {
      if (chdir(cmd[1]) != 0)
        {
          write_error("No such file or directory.\n");
          return (1);
        }
    }
  my_setenv(lenv, "PWD", getcwd(buf, 200));
  return (0);
}

int		get_home(t_list *lenv, char **ptr_home)
{
  int		i;
  int		j;
  t_list	*tmp;
  char		*home;

  i = 0;
  j = 0;
  tmp = find_elem(lenv, "HOME");
  while (tmp->str[i])
    i = i + 1;
  if ((home = malloc(sizeof(char) * i)) == NULL)
    exit(1);
  i = 5;
  while (tmp->str[i])
    home[j++] = tmp->str[i++];
  home[j] = 0;
  *ptr_home = home;
  return (0);
}

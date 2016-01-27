/*
** utils.c for minishell1 in /home/champi_t/rendu/minishell1
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Fri Jan 15 15:56:25 2016 theo champion
** Last update Sun Jan 24 22:42:32 2016 theo champion
*/

#include "header.h"

char	*my_getenv(char **env, char *tofind)
{
  int	i;
  int	h;
  char	*path;
  int	finded;

  h = 0;
  finded = 0;
  while (finded == 0)
    {
      i = 0;
      while (env[h][i] == tofind[i])
        i = i + 1;
      if (env[h][i++] == '=')
        finded = h;
      else
        h = h + 1;
    }
  if ((path = malloc(sizeof(char) * my_strlen(env[finded]))) == NULL)
    exit(1);
  h = 0;
  while (env[finded][i])
    path[h++] = env[finded][i++];
  path[h] = 0;
  return (path);
}

void	write_error(char *error)
{
  int	i;

  i = 0;
  while (error[i])
    write(2, &error[i++], 1);
}

int	try_path(char *path, char **cmd, int i)
{
  int	h;
  int	j;
  char	*final_path;

  h = 0;
  j = 0;
  final_path = malloc(sizeof(char) * (my_strlen(path) + my_strlen(cmd[0])));
  while (path[i] && path[i] != ':')
    final_path[j++] = path[i++];
  final_path[j++] = '/';
  while (cmd[0][h])
    final_path[j++] = cmd[0][h++];
  final_path[j] = 0;
  if (access(final_path, F_OK) != -1)
    {
      cmd[0] = final_path;
      return (0);
    }
  free(final_path);
  return (1);
}

int	free_all(char **array)
{
  int	i;

  i = 0;
  if (!array)
    return (1);
  while (array[i])
    free(array[i++]);
  free(array);
  return (0);
}

void	copy_environ(char ***env, char **environ)
{
  char	*str;
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (environ[i])
    i = i + 1;
  if ((*env = malloc(sizeof(char *) * (i + 2))) == NULL)
    exit(1);
  i = 0;
  while (environ[i])
    {
      while (environ[i][j])
        j = j + 1;
      if ((str = malloc(sizeof(char) * (j + 2))) == NULL)
        exit(1);
      j = 0;
      while (environ[i][j])
        str[j] = environ[i][j++];
      str[j] = 0;
      (*env)[i] = str;
      i = i + 1;
    }
  (*env)[i] = NULL;
}

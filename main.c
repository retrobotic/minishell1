/*
** main.c for minishell in /home/champi_t/rendu/minishell1
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Mon Jan 11 20:25:17 2016 theo champion
** Last update Sun Jan 24 22:41:42 2016 theo champion
*/

#include "header.h"

t_list	*execute_builtin(char **cmd, t_list *lenv, int *ptr_status)
{
  if (my_strcmp(cmd[0], "cd") == 0)
    my_cd(cmd, lenv);
  else if (my_strcmp(cmd[0], "setenv") == 0)
    lenv = my_setenv(lenv, cmd[1], cmd[2]);
  else if (my_strcmp(cmd[0], "unsetenv") == 0)
    lenv = my_unsetenv(lenv, cmd);
  else if (my_strcmp(cmd[0], "env") == 0)
    my_env(lenv);
  else if (my_strcmp(cmd[0], "exit") == 0)
    {
      *ptr_status = 2;
      return (lenv);
    }
  else
    {
      *ptr_status = 0;
      return (lenv);
    }
  *ptr_status = 1;
  return (lenv);
}

int	path_validation(char *path, char **cmd)
{
  int	i;
  int	j;
  int	h;

  i = 0;
  while (path[i])
    {
      if (try_path(path, cmd, i) == 0)
        return (0);
      i = i + 1;
    }
  if (cmd[0][0] == '.' && cmd[0][1] == '/')
    return (0);
  write_error("Command not found.\n");
  return (1);
}

int	fork_and_execute(char **cmd, char **env)
{
  int	pid;

  pid = fork();
  if (pid == -1)
    return (1);
  else if (pid == 0)
    {
      execve(cmd[0], cmd, env);
      exit(0);
    }
  else
    wait(0);
}

int	exe_system_cmd(char **env, char **cmd)
{
  char	*path;

  path = my_getenv(env, "PATH");
  if (path_validation(path, cmd) == 0)
    fork_and_execute(cmd, env);
  free(path);
  return (0);
}

int		main(int argc, char **argv, char **environ)
{
  char		*line;
  char		**cmd;
  t_list	*lenv;
  int		status;
  char		**env;

  status = 0;
  copy_environ(&env, environ);
  while (status != 2)
    {
      my_putstr("my_shell$>");
      lenv = fill_list(env);
      line = get_next_line(0);
      if (cmd = my_str_to_wordtab(line, argc))
        {
          lenv = execute_builtin(cmd, lenv, &status);
          if (status == 0)
            exe_system_cmd(env, cmd);
          env = my_list_to_tab(lenv, env);
        }
      free_all(cmd);
      free(line);
    }
}

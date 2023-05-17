#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void execution(char *command, char **args) {
  char *path;
  char **dir;
  int i;
  i = 0;
  if (ft_strchr(command, '/'))
    path = command;
  else {
    dir = ft_split(getenv("PATH"), ':');
    while (dir[i]) {
      path = ft_strjoin(dir[i], "/");
      path = ft_strjoin(path, command);
      if (access(path, X_OK) == 0)
        break;
      i++;
    }
  }

  if (execve(path, args, NULL) == -1) {
    perror("execve");
    exit(EXIT_FAILURE);
  }
}


int builtin_cmd(char *command, char **args, t_env *head) {
  if (ft_strcmp(command, "cd") == 0) {
    ft_cd(args[1]);
    return 1;
  }
  if (ft_strcmp(command, "pwd") == 0) {
    ft_pwd(1);
    return 1;
  }
  if (ft_strcmp(command, "echo") == 0) {
    ft_echo(args);
    return 1;
  }
  if (ft_strcmp(command, "exit") == 0) {
    exit(1);
    return 1;
  }
  if (ft_strcmp(command, "env") == 0) {
    print_env(head, 0);
    return 1;
  }
  if (ft_strcmp(command, "unset") == 0) {
        unset_env(args, head);
    return 1;
  }
  if (ft_strcmp(command, "export") == 0) {

    if (args == NULL) {
      t_env *tmp;
      tmp = copy_env(head);
      sort_env(&tmp);
      print_env(tmp, 1);
      free_env(tmp);
      return 1;
    } else {
      set_env(args, head);
      print_env(head, 1);
      return 1;
    }
    return 1;
  }
  return 0;
}

void unset_env(char **args, t_env *head) {
  int i;
  i = 0;
  while (args[i]) {
    delete_env(head, args[i]);
    i++;
  }
}

void delete_env(t_env *head, char *name) {
  t_env *tmp;
  t_env *prev;
  tmp = head;
  prev = NULL;
  while (tmp) {
    if (ft_strcmp(tmp->name, name) == 0) {
      if (prev == NULL) {
        head = tmp->next;
        free(tmp);
        return;
      } else {
        prev->next = tmp->next;
        free(tmp);
        return;
      }
    }
    prev = tmp;
    tmp = tmp->next;
  }
}
int chek_plus(char *str) {

  int j;

  j = 0;
  while (str[j]) {
    if (str[j] == '+' && str[j + 1] == '=' && ft_isalpha(str[j - 1]))
      return 1;
    j++;
  }
  return 0;
}

void serch_replace(t_env *head, char *name, char *value) {
  t_env *tmp;
  tmp = head;
  while (tmp) {
    if (ft_strcmp(tmp->name, name) == 0) {
      value++;
      tmp->value = ft_strjoin(tmp->value, value);
      return;
    }
    tmp = tmp->next;
  }
}

int check_heredoc(char **del) {
  int count;
  char *input;
  int fd;
  int i;

  i = 0;
  input = readline("heredoc>");
  fd = open("...", O_RDWR | O_CREAT | O_APPEND, 0777);

  count = arr_len(del);
  if (count == 1) {
    while (ft_strcmp(input, del[count - 1]) != 0) {
      if (ft_strcmp(input, del[count - 1]) != 0)
        ft_putendl_fd(input, fd);
      input = readline("heredoc>");
    }
  } else {
    while (i < count - 1) {
      if (ft_strcmp(input, del[i]) == 0)
        i++;
      input = readline("heredoc>");
    }
    while (ft_strcmp(input, del[count - 1]) != 0) {
      if (ft_strcmp(input, del[count - 1]) != 0)
        ft_putendl_fd(input, fd);
      input = readline("heredoc>");
    }
  }
  close(fd);
  fd = open("...", O_RDONLY);
  unlink("...");
  free(input);
  return fd;
}

int create_in_files(t_cmd *p_cmd) {
  int i;
  int fd;

  i = 0;
  fd = 0;
  while (p_cmd->infile[i]) {
    if (access(p_cmd->infile[i], F_OK) == 0) {
      fd = open(p_cmd->infile[i], O_RDWR);
      if (fd == -1) {
        perror("open");
        return 0;
      }
    } else {
      printf("%s No such file or directory\n", p_cmd->infile[i]);
    }
    if (p_cmd->infile[i + 1] != NULL)
      close(fd);
    i++;
  }
  return (fd);
}

int create_out_files(t_cmd *p_cmd) {
  int i;
  int fd;

  i = 0;
  fd = 0;
  while (p_cmd->outfile[i]) {
    if (p_cmd->is_red_or_app == 0)
      fd = open(p_cmd->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
    else
      fd = open(p_cmd->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0777);
    if (fd == -1) {
      perror("open");
      return 0;
    }
    if (p_cmd->outfile[i + 1] != NULL)
      close(fd);
    i++;
  }
  dup2(fd, 1);
  // bach cat tkhrj 3la l terminal
  dup2(fd, 0);
  close(fd);
  return (fd);
}

int ft_pwd(int fd) {
  char *pwd;

  pwd = getcwd(NULL, 0);
  ft_putstr_fd(pwd, fd);
  ft_putstr_fd("\n", fd);
  free(pwd);
  return 1;
}

void signal_handler(int signum) {
  if (signum == SIGINT)
    exit(130);
}

int ft_close_file(int fd) {
  if (close(fd) == -1) {
    perror("close");
    return 0;
  }
  return 1;
}

int is_all_new_line(char *str) {
  int i;

  i = 0;
  if (str[0] == '-') {
    i++;
    while (str[i]) {
      if (str[i] != 'n')
        return 0;
      i++;
    }
    return 1;
  }
  return 0;
}

int ft_echo(char **argv) {
  int i;
  i = 0;

  while (argv[i]) {
    if (is_all_new_line(argv[0]) == 1)
      i++;
    ft_putstr_fd(argv[i], 1);
    i++;
  }
  if (is_all_new_line(argv[0]) != 1)
    ft_putstr_fd("\n", 1);
  return 1;
}

void ft_lstback(t_env **head, char *key, char *value) {
  t_env *new = (t_env *)malloc(sizeof(t_env));
  if (!new)
    return;
  new->name = ft_strdup(key);
  new->value = ft_strdup(value);
  new->next = NULL;

  if (*head == NULL) {
    *head = new;
    return;
  }

  t_env *current = *head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = new;
}

void free_arr(char **arr) {
  int i;

  i = 0;
  while (arr[i]) {
    free(arr[i]);
    i++;
  }
  free(arr);
}

char *get_name(char *str) {
  int i;
  char *name;

  i = 0;
  while (str[i] && str[i] != '=' && str[i] != '+')
    i++;
  name = (char *)malloc(sizeof(char) * (i + 1));
  if (!name)
    return NULL;
  i = 0;
  while (str[i] && str[i] != '=' && str[i] != '+') {
    name[i] = str[i];
    i++;
  }
  name[i] = '\0';
  return name;
}

char *get_value(char *str) {
  int i;
  int j;

  char *value;
  i = 0;
  j = 0;

  while (str[i] && str[i] != '=')
    i++;
  while (str[i + j])
    j++;
  value = (char *)malloc(sizeof(char) * (j + 1));
  if (!value)
    return NULL;
  j = 0;
  while (str[i]) {
    value[j] = str[i];
    i++;
    j++;
  }
  value[j] = '\0';
  return value;
}

t_env *set_env(char **env, t_env *head) {
  int i;

  i = 0;
  while (env[i]) {

    if (chek_plus(env[i]))
      serch_replace(head, get_name(env[i]), get_value(env[i]));
    else if (ft_strchr(env[i], '=')) {
      ft_lstback(&head, get_name(env[i]), get_value(env[i]));
    } else
      ft_lstback(&head, get_name(env[i]), get_value(env[i]));

    i++;
  }
  return head;
}

t_env *copy_env(t_env *head) {
  t_env *head2;
  t_env *tmp;

  head2 = NULL;
  tmp = head;
  while (tmp) {
    ft_lstback(&head2, tmp->name, tmp->value);
    tmp = tmp->next;
  }
  return head2;
}
t_env *sort_env(t_env **head) {
  t_env *tmp;
  t_env *tmp2;
  char *tmp_name;
  char *tmp_value;

  tmp2 = *head;
  while (tmp2) {
    tmp = *head;
    while (tmp) {
      if (ft_strcmp(tmp->name, tmp2->name) > 0) {
        tmp_name = tmp->name;
        tmp_value = tmp->value;
        tmp->name = tmp2->name;
        tmp->value = tmp2->value;
        tmp2->name = tmp_name;
        tmp2->value = tmp_value;
      }
      tmp = tmp->next;
    }
    tmp2 = tmp2->next;
  }
  return *head;
}
void print_env(t_env *env, int i) {
  if (!env)
    return;
  t_env *tmp;
  tmp = env;
  while (tmp) {
    if (i == 1) {
      printf("declare -x %s%.1s\"%s\"\n", tmp->name, tmp->value,
             tmp->value + 1);

    } else
      printf("%s%s\n", tmp->name, tmp->value);
    tmp = tmp->next;
  }
}

void free_env(t_env *env) {
  t_env *tmp;

  while (env) {
    tmp = env;
    env = (env)->next;
    free(tmp->name);
    free(tmp->value);
    free(tmp);
  }
  free(env);
}

void ft_cd(char *argv) {
  if (chdir(argv) != 0) {
    {
      perror("cd");
      exit(1);
    }
    return;
  }
}
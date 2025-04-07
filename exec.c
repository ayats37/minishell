#include "minishell.h"

t_env *env_list = NULL;

int    ft_cd(t_token *path, t_lexer *lexer)
{
    path = get_next_token(lexer);
    // printf("path= %s\n", path->value);
  if (chdir(path->value) != 0)
  {
    printf("cd: %s: No such file or directory\n", path->value);
    return (1);
  }
  return (0);
}
int ft_pwd()
{
    char cwd[10240];
    if (!getcwd(cwd, sizeof(cwd)))
    {
        printf("error");
        return(1);
    }
    printf("%s\n", cwd);
    return (0);
}
int ft_echo(t_lexer *lexer)
{
    int new_line;
    char *var_value;

    new_line = 1;
    t_token *string = get_next_token(lexer);

    // printf("%c", string->value[0]);
    if (string && (strcmp(string->value, "-n") == 0))
    {
        new_line = 0;
        string  = get_next_token(lexer);
    }
    while (string) 
    {
        if (string)
        {
            if (string->value[0] == '$')
            {
                var_value = get_env_value(string->value + 1);
                if(var_value)
                    printf("%s", var_value);
            }
            else
                printf("%s", string->value);
        }
        string = get_next_token(lexer);
        if (string)
            printf(" ");
    }
    if (new_line)
        printf("\n");
    return (0);
       
}

int ft_export(t_token *input, t_lexer *lexer)
{
   char *equal_sign;
   char *name;
   char *value;
    input = get_next_token(lexer);

   equal_sign = ft_strchr(input->value, '=');
   if (!equal_sign)
        return(1);
   name = strndup(input->value, equal_sign - input->value);
   value = ft_strdup(equal_sign + 1);
   update_env(name, value);
   free(name);
   free(value);
   return (0);
}

void update_env(char *name, char *value)
{
    t_env *current = env_list;
    t_env *new_env;

    while (current)
    {
        if ((strcmp(current->name, name) == 0))
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    new_env = malloc(sizeof (t_env));
    new_env->name = ft_strdup(name);
    new_env->value = ft_strdup(value);
    new_env->next = env_list;
    env_list = new_env;
}
char *get_env_value(char *name)
{
    t_env *current = env_list;

    while (current)
    {
        if (strcmp(current->name, name) == 0)
            return (current->value);
        current = current->next;
    }
    return(NULL);
}

int execute_builtin(t_token *token, t_lexer *lexer)
{
    if (strcmp(token->value, "echo") == 0)
        ft_echo(lexer);
    if (strcmp(token->value, "cd") == 0)
        return(ft_cd(token, lexer));
    if (strcmp(token->value, "pwd") == 0)
        return (ft_pwd());
    if (strcmp(token->value, "export") == 0)
        return(ft_export(token, lexer));
    // if (strcmp(token->value, "unset") == 0)
    // if (strcmp(token->value, "env") == 0)
    // if (strcmp(token->value, "exit") == 0)§
    return (0);
}


int	main(int argc, char **argv)
{
	char	*input;
	t_lexer	*lexer;
	t_token	*token;
 

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		lexer = initialize_lexer(input);
		while (lexer->position < lexer->lenght)
		{
			token = get_next_token(lexer);
			if (!token->value)
				return (0);
			token->type = token_type(token);
			token->prece = precedence_type(token);
            // printf("%s\n", token->value);
			execute_builtin(token, lexer);
		}
	}
	return (0);
}


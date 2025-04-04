#include "minishell.h"

t_lexer *initialize_lexer(char *input)
{
	t_lexer *lexer;

	lexer = malloc((sizeof(t_lexer)));
	if (!lexer)
		return (NULL);
	lexer->input  = input;
	lexer->lenght = ft_strlen(input);
	lexer->position = 0;
	return (lexer);
}

int	is_space(t_lexer *lexer)
{
	if((lexer->input[lexer->position] >= 9 && lexer->input[lexer->position] <= 13) || lexer->input[lexer->position] == 32)
		return (1);
	return (0);
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->position < lexer->lenght && is_space(lexer))
		lexer->position++;
}

t_token	*handle_quote(t_lexer *lexer, char quote)
{
	size_t	lenght;
	size_t	start;
	char	*cmd;

	start = lexer->position + 1;
	while(lexer->position < lexer->lenght && lexer->input[lexer->position] != quote)
		lexer->position++;
	if (lexer->position >= lexer->lenght)
		return NULL;
	lenght = lexer->position - start;
	cmd = ft_substr(lexer->input, start, lenght);
	printf("%s\n", cmd);
	return NULL;
}

// t_token *create_token(char *value)
// {
// 	t_token *token;

// 	token = malloc(sizeof(t_token));
// 	if(!token)
// 		return (NULL);
// 	else
// 	{
// 		token->args = ft_strdup(value);
// 		token->next = NULL;
// 	}
// 	return(token);
// }

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *input;
	t_lexer *lexer;
	char current;

	while(1)
	{
		input  = readline("minishell> ");
		lexer = initialize_lexer(input);
		// printf("position = %d\n", lexer->position);
		// printf("lenght = %d\n", lexer->lenght);
		// printf("input = %s\n\n\n", lexer->input);
		skip_whitespace(lexer);
		// printf("position = %d\n", lexer->position);
		// printf("lenght = %d\n", lexer->lenght);
		// printf("input = %s\n", lexer->input);
		if (lexer->position >= lexer->lenght)
			return 1;
		current = lexer->input[lexer->position];
		if (current == '\'' || current == '"')
			handle_quote(lexer, current);
		// printf("input = %s\n", input);
	}
	return (0);
}
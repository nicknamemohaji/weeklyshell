#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

typedef enum e_status {
    FALSE,
    SQUOTE,
    DQUOTE,
    PAREN
} t_status;

# define RL_EOF (void *)0


int main(void)
{
    char *input;
    t_status input_status = FALSE;

    while (1)
    {
        if (input_status == FALSE)
            input = readline("prompt> ");
        else
            input = readline("> ");
        
        if (input == RL_EOF)
        {
            
        }
        if (*input != '\0')
            add_history(input);
        printf("You entered: %s\n", input);
        free(input);
    }
}
#include "t_error.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static size_t	str_length(const char *str);
static void		append_str(char *onto, const char *str);

#define MAX_MESSAGE_LEN 100

void	log_error(t_error err)
{
	char	message[MAX_MESSAGE_LEN];
	size_t	message_len;

	message_len = str_length("Error: \n") + str_length(err_representation(err));
	if (MAX_MESSAGE_LEN < message_len)
		return ;
	memset(message, '\0', MAX_MESSAGE_LEN);
	append_str(message, "Error: ");
	append_str(message, err_representation(err));
	append_str(message, "\n");
	write(STDERR_FILENO, message, str_length(message));
}

static size_t	str_length(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	append_str(char *onto, const char *str)
{
	size_t	len_onto;
	size_t	len_str;
	size_t	i;

	len_onto = str_length(onto);
	len_str = str_length(str);
	i = 0;
	while (i < len_str)
	{
		onto[len_onto + i] = str[i];
		i++;
	}
	onto[len_onto + i] = '\0';
}

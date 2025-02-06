#include "t_error/t_error.h"

#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>

static bool		is_valid_number(const char *word);
static bool		is_digit(char ch);
static bool		will_overflow(uint32_t num, uint8_t addend);
static uint8_t	parse_digit(char ch);

t_error	parse_uint32(const char *str, uint32_t *result_out)
{
	size_t	i;

	i = 0;
	if (!is_valid_number(str))
		return (E_INVALID_ARGUMENT);
	*result_out = 0;
	while (is_digit(str[i]))
	{
		if (will_overflow(*result_out, parse_digit(str[i])))
			return (E_OUT_OF_RANGE);
		*result_out *= 10;
		*result_out += parse_digit(str[i]);
		i++;
	}
	return (0);
}

static bool	is_valid_number(const char *word)
{
	size_t	i;

	i = 0;
	while (word[i] == ' ')
		i++;
	if (word[i] == '-' || word[i] == '+')
		return (false);
	if (word[i] == '\0')
		return (false);
	while (is_digit(word[i]))
		i++;
	if (word[i] != '\0')
		return (false);
	return (true);
}

static bool	is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

static bool	will_overflow(uint32_t num, uint8_t addend)
{
	if (num > UINT32_MAX / 10)
		return (true);
	num *= 10;
	if (num > UINT32_MAX - addend)
		return (true);
	return (false);
}

static uint8_t	parse_digit(char ch)
{
	return (ch - '0');
}

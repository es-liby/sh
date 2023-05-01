#include <libft.h>

bool	ft_isallspace(const char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (*str == 0);
}

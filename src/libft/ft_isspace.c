#include <libft.h>

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
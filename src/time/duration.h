#ifndef INSTANT_H
# define INSTANT_H

# include "./instant.h"

# include <stdint.h>

typedef int64_t	t_duration;

t_duration	duration_since(t_instant from, t_instant to);
t_duration	duration_since_ms(t_instant from, t_instant to);

#endif // INSTANT_H

#include "t_error.h"

#define REPR_NO_ERROR "success"
#define REPR_NONE "unknown error"

// input errors
#define REPR_BAD_USAGE "bad usage"
#define REPR_EXPECTED_NUM "expected numeric value"
#define REPR_OUT_OF_RANGE "value is outside of range"

// programming errors
#define REPR_UNMATCHED_PATTERN "unmatched pattern"

// system call errors
#define REPR_PTHREAD_MUTEX_INIT "pthread_mutex_init"
#define REPR_PTHREAD_MUTEX_LOCK "pthread_mutex_lock"
#define REPR_PTHREAD_MUTEX_UNLOCK "pthread_mutex_unlock"
#define REPR_PTHREAD_CREATE "pthread_create"

// lib function errors
#define REPR_MALLOC "malloc"

const char	*err_representation(t_error err)
{
	if (err == E_BAD_USAGE)
		return (REPR_BAD_USAGE);
	if (err == E_EXPECTED_NUM)
		return (REPR_EXPECTED_NUM);
	if (err == E_OUT_OF_RANGE)
		return (REPR_OUT_OF_RANGE);
	if (err == E_UNMATCHED_PATTERN)
		return (REPR_UNMATCHED_PATTERN);
	if (err == E_PTHREAD_MUTEX_INIT)
		return (REPR_PTHREAD_MUTEX_INIT);
	if (err == E_PTHREAD_MUTEX_LOCK)
		return (REPR_PTHREAD_MUTEX_LOCK);
	if (err == E_PTHREAD_MUTEX_UNLOCK)
		return (REPR_PTHREAD_MUTEX_UNLOCK);
	if (err == E_PTHREAD_CREATE)
		return (REPR_PTHREAD_CREATE);
	if (err == E_MALLOC)
		return (REPR_MALLOC);
	return (REPR_NONE);
}

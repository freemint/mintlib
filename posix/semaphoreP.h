#include <semaphore.h>
#include <limits.h>

# define SEM_VALUE_SHIFT 1
# define SEM_NWAITERS_MASK ((unsigned long)1)

#define SEM_SHM_PREFIX  "sem."

/* The directory that contains shared POSIX objects.  */
#define SHMDIR "U:\\shm\\"

struct shmdir_name
{
  /* The combined prefix/name.  The sizeof includes the terminating
     NUL byte.  4 bytes are needed for the optional "sem." prefix.  */
  char name[sizeof (SHMDIR) + 4 + NAME_MAX];
};

/* Sets RESULT->name to the constructed name and returns 0 on success,
   or -1 on failure.  Includes the "sem." prefix in the name if
   SEM_PREFIX is true.  */
int __shm_get_name (struct shmdir_name *result, const char *name,
		    int sem_prefix);

static inline int valid_nanoseconds(long ns)
{
	return 0 <= ns && ns < 1000000000L;
}

int __sem_wait_fast(sem_t *sem, int definitive_result);
int __sem_wait_slow(sem_t *sem, __clockid_t clockid, const struct timespec *abstime);

/*
 * pseudo "atomic" functions for now
 */

#define atomic_load_relaxed(mem) *(mem)
#define atomic_compare_exchange_weak_release(mem, expected, desired) (*(mem) = desired, 1)
#define atomic_compare_exchange_weak_acquire(mem, expected, desired) (*(mem) = desired, 1)
#define atomic_fetch_and_acquire(mem, val) (*(mem) &= val)
#define atomic_fetch_or_relaxed(mem, val) (*(mem) |= val)
#define atomic_fetch_add_release(mem, val) *(mem) += val
#define atomic_fetch_add_acquire(mem, val) atomic_fetch_add_release(mem, val)

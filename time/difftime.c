/* return difference between two time_t types -- ERS*/

#include <time.h>

double difftime(t2, t1)
time_t t2, t1;
{
	return (double) (t2 - t1);
}

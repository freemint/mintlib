/* return difference between two time_t types -- ERS*/

#include <time.h>

double
difftime(time_t t2, time_t t1)
{
	return (double)(t2 - t1);
}

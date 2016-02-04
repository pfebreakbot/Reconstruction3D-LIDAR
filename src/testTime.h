#ifndef testTime
#define testTime
/**********************************************************************************************************************************/
#include <time.h>
#include <stdio.h>
#define TIME_INIT	struct timespec time1, time2;
#define TIME_START 	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);
#define TIME_STOP	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time2);printf("%ld,%09lds\n",diff(time1,time2).tv_sec,diff(time1,time2).tv_nsec);
struct timespec diff(struct timespec start,struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) 
	{
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	}
	else 
	{
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
/**********************************************************************************************************************************/
#endif

/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "status.h"
#include <pthread.h>

void *
status_2_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	printf("Result: %d\n", *argp);

	return (void *) &result;
//	result = *argp;
//	pthread_exit(&result);
}

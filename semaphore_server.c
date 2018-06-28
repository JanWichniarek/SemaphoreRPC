/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "semaphore.h"
#include "SemaphoreLib.h"

void *
up_1_svc(semaphore_arg *argp, struct svc_req *rqstp)
{
	static char * result;

    semUp(argp->amount,argp->version, rqstp);

	return (void *) &result;
}

void *
down_1_svc(semaphore_arg *argp, struct svc_req *rqstp)
{
	static char * result;

    semDown(argp->amount,argp->version, rqstp);

	return (void *) &result;
}

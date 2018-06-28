/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

int counter;

static void
semaphore_2(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int status_2_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case status:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) status_2_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	//svc_sendreply(transp, (xdrproc_t) _xdr_result, result);
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
	//if (result != NULL ) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
    if(counter==0){
        svc_exit();
    }
    counter--;
    //pthread_exit(&result);
	return;
}

void* startServer(void* p)
{
    threaddata_t*x=(threaddata_t*)p;
    int version = x->version;
    counter = x->counter;
    pthread_barrier_wait(x->pbarrier);

	register SVCXPRT *transp;

	pmap_unset (SEMAPHORE, version);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, SEMAPHORE, version, semaphore_2, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (SEMAPHORE, Callback, udp).");
		exit(1);
	}

    printf("Server started \n");

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
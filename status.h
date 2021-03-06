/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _STATUS_H_RPCGEN
#define _STATUS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define SEMAPHORE 0x20000000
#define Callback 2

typedef struct threaddata_ {
    pthread_barrier_t* pbarrier;
    int version;
    int counter;
} threaddata_t;


#if defined(__STDC__) || defined(__cplusplus)
#define status 1
extern  void * status_2(int *, CLIENT *);
extern  void * status_2_svc(int *, struct svc_req *);
extern int semaphore_2_freeresult (SVCXPRT *, xdrproc_t, caddr_t);
void* startServer(void*);


#else /* K&R C */
#define status 1
extern  void * status_2();
extern  void * status_2_svc();
extern int semaphore_2_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_STATUS_H_RPCGEN */

//
// Created by jan on 21.05.18.
//
#include "SemaphoreLib.h"
#include <sys/queue.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include "status.h"
#include <unistd.h>
#include <arpa/inet.h>


static int semaphoreValue = 10;
TAILQ_HEAD(tailhead, queueEntry) head;

struct queueEntry{
    int value;
    int version;
    struct sockaddr_in* address;
    TAILQ_ENTRY(queueEntry) tail;
};

void initQueue(){
    TAILQ_INIT(&head);
}

void semUp(int value, int version, struct svc_req *rqstp){
    semaphoreValue+=value;
    sendStatusToClient(svc_getcaller(rqstp->rq_xprt),version);
}

void semDown(int value, int version, struct svc_req *rqstp){
    if(semaphoreValue>value){
        semaphoreValue-=value;
        sendStatusToClient(svc_getcaller(rqstp->rq_xprt),version);
    }else{
        addToQueue(value, version, svc_getcaller(rqstp->rq_xprt));
    }
}

void addToQueue(int value, int version, struct sockaddr_in* address){
    struct queueEntry* entry;
    entry = malloc(sizeof(struct queueEntry));

    entry->address->sin_addr = address->sin_addr;
    entry->address->sin_family = address->sin_family;
    entry->version = version;
    entry->value = value;

    TAILQ_INSERT_TAIL(&head, entry, tail);
}

void
semaphore_2(char* host,int version)
{
    CLIENT *clnt;
    void  *result_1;
    int  status_2_arg;
#ifndef	DEBUG
    clnt = clnt_create (host, SEMAPHORE, Callback, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
#endif	/* DEBUG */
    result_1 = status_2(&status_2_arg, clnt);
    if (result_1 == (void *) NULL) {
        clnt_perror (clnt, "call failed");
    }
#ifndef	DEBUG
    clnt_destroy (clnt);
    clnt = NULL;
#endif	 /* DEBUG */
}

void tryRemoveFromQueue(){
    if(head.tqh_first!=NULL){
        if(semaphoreValue>head.tqh_first->value){
            semaphoreValue-=head.tqh_first->value;
            sendStatusToClient(head.tqh_first->address, head.tqh_first->version);

            TAILQ_REMOVE(&head, head.tqh_first, tail);
            if(head.tqh_first!=NULL){
                tryRemoveFromQueue();
            }
        }
    }

}

void sendStatusToClient(struct sockaddr_in* address, int version){
    address->sin_port = htons(111);
    struct timeval timeval1 = {15,0};
    int in = 0;
    char out = 0;
    unsigned long portp = 0;

    pmap_rmtcall(address,0x20000000,version,1,(xdrproc_t)xdr_int,(caddr_t)&in,(xdrproc_t)xdr_void,&out,timeval1,&portp);

    printf("Semaphore value: %d\n", semaphoreValue);
}

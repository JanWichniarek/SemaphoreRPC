//
// Created by jan on 21.05.18.
//

#ifndef SEMAPHORERPC_SEMAPHORE_H
#define SEMAPHORERPC_SEMAPHORE_H

#include <sys/queue.h>
#include <stdio.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>



void initQueue();

void semUp(int value, int version, struct svc_req *rqstp);
void semDown(int value, int version, struct svc_req *rqstp);

void addToQueue(int value, int version, struct sockaddr_in* address);
void tryRemoveFromQueue();
void sendStatusToClient(struct sockaddr_in* address, int version);

#endif //SEMAPHORERPC_SEMAPHORE_H

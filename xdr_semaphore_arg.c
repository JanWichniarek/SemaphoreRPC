//
// Created by root on 09.06.18.
//
#include "semaphore.h"

bool_t
xdr_semaphore_arg (XDR *xdrs, semaphore_arg *objp)
{
    register int32_t *buf;

    if (!xdr_int (xdrs, &objp->amount))
        return FALSE;
    if (!xdr_int (xdrs, &objp->version))
        return FALSE;
    return TRUE;
}

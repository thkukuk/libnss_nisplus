/* Copyright (C) 1997-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Thorsten Kukuk <kukuk@uni-paderborn.de>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _NIS_NSS_NISPLUS_H
#define _NIS_NSS_NISPLUS_H	1

#include <rpcsvc/nis.h>

/* Convert NIS+ error number to NSS error number.  */
extern const enum nss_status __niserr2nss_tab[];
extern const unsigned int __niserr2nss_count;

static enum nss_status
__attribute__ ((unused))
niserr2nss (int errval)
{
  if ((unsigned int) errval >= __niserr2nss_count)
    return NSS_STATUS_UNAVAIL;
  return __niserr2nss_tab[(unsigned int) errval];
}

/* lookup_actions, service_library and service_user are
   from glibc nsswitch.h header file. */

/* Actions performed after lookup finished.  */
typedef enum
{
  NSS_ACTION_CONTINUE,
  NSS_ACTION_RETURN
} lookup_actions;

typedef struct service_library
{
  /* Name of service (`files', `dns', `nis', ...).  */
  const char *name;
  /* Pointer to the loaded shared library.  */
  void *lib_handle;
  /* And the link to the next entry.  */
  struct service_library *next;
} service_library;

typedef struct service_user
{
  /* And the link to the next entry.  */
  struct service_user *next;
  /* Action according to result.  */
  lookup_actions actions[5];
  /* Link to the underlying library object.  */
  service_library *library;
  /* Collection of known functions.  */
  void *known;
  /* Name of the service (`files', `dns', `nis', ...).  */
  char name[0];
} service_user;

/* Internal function from glibc/libnsl */
extern struct ib_request *__create_ib_request (const_nis_name name,
                                               unsigned int flags);
extern  bool_t _xdr_ib_request (XDR *, ib_request*);
extern  bool_t _xdr_nis_result (XDR *, nis_result*);
extern nis_error __prepare_niscall (const_nis_name name, directory_obj **dirp,
                                    dir_binding *bptrp, unsigned int flags);
extern nis_error __do_niscall3 (dir_binding *dbp, u_long prog,
                                xdrproc_t xargs, caddr_t req,
                                xdrproc_t xres, caddr_t resp,
                                unsigned int flags, void *cb);
extern nis_error __follow_path (char **tablepath, char **tableptr,
                                struct ib_request *ibreq, dir_binding *bptr);

/* makes code easier to port */
#define atomic_compare_and_exchange_bool_acq(mem, newval, oldval) \
  ({ __typeof (mem) __gmemp = (mem);                                  \
     __typeof (*mem) __gnewval = (newval);                            \
                                                                      \
     *__gmemp == (oldval) ? (*__gmemp = __gnewval, 0) : 1; })


#endif /* src/nss-nisplus.h */

/* -------------------------------------------------------------------------- */
/* Copyright 2002-2006 GridWay Team, Distributed Systems Architecture         */
/* Group, Universidad Complutense de Madrid                                   */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#ifndef _GW_HOST_POOL_H
#define _GW_HOST_POOL_H

#include <pthread.h>
#include "gw_host.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

typedef struct gw_host_pool_s
{
    pthread_mutex_t mutex;

    int number_of_hosts;
    int last_host_id;

    gw_host_t **pool;

} gw_host_pool_t;

gw_host_pool_t* gw_host_pool_init();

/* -------------------------------------------------------------------------- */

void gw_host_pool_finalize();

int gw_host_pool_host_allocate (char * hostname, 
                                int    nice,
                                char * em_mad, 
                                char * tm_mad, 
                                char * im_mad);

void gw_host_pool_host_free (int host_id);

gw_host_t* gw_host_pool_get_host (int host_id, gw_boolean_t lock);

gw_host_t* gw_host_pool_search (char *hostname, gw_boolean_t lock);

void gw_host_pool_update (char * hostnames, 
                          int    nice, 
                          char * em_mad,
                          char * tm_mad, 
                          char * im_mad);

void gw_host_pool_print (FILE *fd);

void gw_host_pool_monitor_hosts( );


#endif

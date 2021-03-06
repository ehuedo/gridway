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

#ifndef _GW_CONF_H
#define _GW_CONF_H

#include "gw_common.h"
#include <time.h>

/* gwd defaults */

#define GW_NUMBER_OF_ARRAYS_DEFAULT 20
#define GW_NUMBER_OF_JOBS_DEFAULT   200
#define GW_NUMBER_OF_HOSTS_DEFAULT  500
#define GW_NUMBER_OF_USERS_DEFAULT  30

#define GW_SCHEDULING_INTERVAL_DEFAULT  30
#define GW_DISCOVERY_INTERVAL_DEFAULT   300
#define GW_MONITORING_INTERVAL_DEFAULT  180

#define GW_GWD_PORT_DEFAULT              6725
#define GW_MAX_NUMBER_OF_CLIENTS_DEFAULT 20

#define GW_MAX_IDLE_TIME                360

#define GW_MAX_JOBS_PER_SCHED           10
#define GW_MAX_JOBS_PER_HOST            10
#define GW_MAX_JOBS_PER_USER            20

/* job template defaults */

#define GW_CHECKPOINT_INTERVAL_DEFAULT  300
#define GW_RESCHEDULE_ON_FAILURE_DEFAULT GW_TRUE
#define GW_NUMBER_OF_RETRIES_DEFAULT     3

#define GW_SUSPENSION_TIMEOUT_DEFAULT 300
#define GW_CPULOAD_THRESHOLD_DEFAULT  70

#define GW_RESCHEDULING_INTERVAL_DEFAULT  0
#define GW_RESCHEDULING_THRESHOLD_DEFAULT 300

#define GW_POLL_INTERVAL_DEFAULT        60

#define GW_WRAPPER_DEFAULT "scripts/wrapper.sh"

/* MADs */
#define GW_MAX_MADS       5

#define GW_MAD_NAME_INDEX 0
#define GW_MAD_PATH_INDEX 1
#define GW_MAD_ARGS_INDEX 2
#define GW_MAD_NICE_INDEX 3
#define GW_MAD_TM_INDEX   4
#define GW_MAD_EM_INDEX   5

/* ------------------------------------------------------------------------- */

typedef struct gw_conf_s
{
    gw_boolean_t multiuser;
    
    char *conf_file;
    char *template_default;
    char *gw_location;
    char *gw_globus_seg;
    char *gw_acct;
    
    char *gwadmin;
    
    int number_of_arrays;
    int number_of_jobs;
    int number_of_hosts;
    int number_of_users;
    
    int jobs_per_sched;
    int jobs_per_user;
    int jobs_per_host;
        
    time_t scheduling_interval;
    time_t poll_interval;
    time_t discovery_interval;
    time_t monitoring_interval;
    
    int  gwd_port;
    int  max_number_of_clients;
    
    char  ***im_mads;
    char  ***tm_mads;
    char  ***em_mads;
    char  **dm_mad;
} gw_conf_t;

/* ------------------------------------------------------------------------- */

extern gw_conf_t gw_conf;

/* ------------------------------------------------------------------------- */

typedef enum {
    GWD_PORT,
    MAX_NUMBER_OF_CLIENTS,
    NUMBER_OF_ARRAYS,
    NUMBER_OF_JOBS,
    NUMBER_OF_HOSTS,
    NUMBER_OF_USERS,
    JOBS_PER_SCHED,
    JOBS_PER_HOST,
    JOBS_PER_USER,
    SCHEDULING_INTERVAL,
    DISCOVERY_INTERVAL,
    MONITORING_INTERVAL,
    POLL_INTERVAL,
    IM_MAD,
    TM_MAD,
    EM_MAD,
    DM_SCHED,
} gw_conf_var_t;

/* ------------------------------------------------------------------------- */

int gw_conf_init (gw_boolean_t multiuser);

int gw_conf_lex_parser ();

int gw_loadconf ();

#endif

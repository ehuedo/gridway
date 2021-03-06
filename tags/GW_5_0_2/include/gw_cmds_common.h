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

#ifndef _GW_CMDS_COMMON_H
#define _GW_CMDS_COMMON_H

#include "gw_rm_msg.h"

/* -------------------------------------------------------------------------- */

#define bold()       printf("\33[1m");
#define underline()  printf("\33[4m");
#define cls()        printf("\33[2J\33[H");
#define move(x,y)    printf("\33[%d;%dH",y,x);
#define restore()    printf("\33[0m");

/* -------------------------------------------------------------------------- */


char *gw_print_time(time_t t, char *the_time);

char *gw_print_time2(time_t t, char *the_time);

char *gw_print_date_and_time(time_t t, char *the_time);

int gw_check_state(char jobstate_from_user, gw_job_state_t current_job_state);

void gw_client_print_status_header(char *outoption);

void gw_client_print_status(gw_msg_job_t * msg, char *outoption);

void gw_client_print_pool_status(char *username, char *hostname, char jobstate, char *outoption, int array_id);

void gw_client_print_history_header();

void gw_client_print_history(gw_msg_history_t *msg_history);

void gw_client_print_host_status_header();

void gw_client_print_host_status(gw_msg_host_t * msg);

void gw_client_print_host_queues(gw_msg_host_t * msg, gw_boolean_t header);

void gw_client_print_host_pool_status();

void gw_client_print_host_match_header();

void gw_client_print_host_match(gw_msg_match_t *match_list);

void gw_client_print_user_header();

void gw_client_print_user(gw_msg_user_t *msg_user);

#ifdef HAVE_LIBDB

void gw_client_print_user_accts_header(const char *user, time_t from_time);
void gw_client_print_host_accts_header(const char *host, time_t from_time);
void gw_client_print_host_and_user_accts_header(const char *host, const char *user, time_t from_time);
void gw_client_print_accts(gw_acct_t **accts, int num);

#endif

#endif

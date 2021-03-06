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

#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "gw_im.h"
#include "gw_host.h"
#include "gw_host_pool.h"
#include "gw_log.h"

void gw_im_listener(void *arg)
{
    fd_set in_pipes;
    
    int    i,j;
    int    host_id;    
    int    greater, rc;
    
    char   c;
    char   info[GW_IM_MAX_INFO];
    char   s_host_id[GW_IM_MAX_HOST_ID];
    char   result[GW_IM_MAX_RESULT];
    char   action[GW_IM_MAX_ACTION];
    char   str[GW_IM_MAX_STRING];    
    
    gw_host_t *   host;
	gw_im_mad_t * im_mad;
	
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
        
    while (1)
    {
		greater = gw_im_set_pipes (&in_pipes);
        
        select(greater+1, &in_pipes, NULL, NULL, NULL);

        for (i=0; i<=greater; i++)
        {            
            if ( FD_ISSET(i, &in_pipes) )
            {         
            	im_mad = gw_im_get_mad_by_fd(i);
            	
            	if ( im_mad == NULL )
            		continue;
            	
                j = 0;

                do
                {
                    rc = read(i, (void *) &c, sizeof(char));
                    str[j++] = c;    
                }
                while ( rc > 0 && c != '\n' );

                str[j] = '\0';

                if (rc <= 0)
					continue;
					                
                info[0] = '\0';

                rc = sscanf(str,"%s %s %s %[^\n]", action, s_host_id, result, info);

        
#ifdef GWIMDEBUG
                gw_log_print("IM",'D',"MAD (%s) message %s %s %s %s (info length=%d).\n",
                        im_mad->name, 
                        action, 
                        s_host_id, 
                        result,
                        info, 
                        strlen(info));
#endif

                if ( rc < 3 )
                {
                    gw_log_print("IM",'E',"Wrong field number in MAD (%s) message: %s.\n",
                            im_mad->name, str);
                    continue;
                }
                

                if (s_host_id[0] != '-')
                {
                    host_id = atoi(s_host_id);                    
                    
                    host = gw_host_pool_get_host (host_id, GW_FALSE);

                    if (host == NULL)
                    {
                        gw_log_print("IM",'E',"Message %s for host %d (does not exist) from MAD (%s).\n",
                                im_mad->name, action, host_id);
                        continue;
                    }
                }
                else
                {
                    host_id = -1;
                }

                if (strcmp(action, "DISCOVER") == 0)
                {
                    if (strcmp(result, "SUCCESS") == 0)
                    {
                        if (strlen(info) > 0)
                        {
                            gw_log_print("IM",'I',"Hosts discovered by MAD (%s): %s\n",
                                    im_mad->name, info);
                                    
                            gw_host_pool_update(info, 
                            		            im_mad->nice,
                                                im_mad->em_mad_name,
                                                im_mad->tm_mad_name,
                                                im_mad->name);
                            
#ifdef GWIMDEBUG
                            gw_host_pool_print(stdout);
#endif
                        }
                        else
                        {
                            gw_log_print("IM",'I',"No hosts discovered by MAD (%s)\n",
                                    im_mad->name);
                        }

                        im_mad->state = GW_IM_MAD_STATE_IDLE;
                    }
                    else
                    {
                        gw_log_print("IM",'E',"DISCOVER error in MAD (%s): %s\n",
                                im_mad->name, info);
                    }
                }
                else if (strcmp(action, "MONITOR") == 0)
                {
                    if (strcmp(result, "SUCCESS") == 0)
                    {
                        gw_host_update(host_id, info);
                    }
                    else
                    {
                        gw_log_print("IM",'E',"MONITOR error in MAD (%s): %s\n",
                                im_mad->name, info);
                                
                        gw_host_clear_dynamic_info(host_id);
                    }
                }
            }
        }
    }
}

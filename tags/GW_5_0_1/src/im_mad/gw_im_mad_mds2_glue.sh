#!/bin/bash

# -------------------------------------------------------------------------- 
# Copyright 2002-2006 GridWay Team, Distributed Systems Architecture         
# Group, Universidad Complutense de Madrid                                   
#                                                                            
# Licensed under the Apache License, Version 2.0 (the "License"); you may    
# not use this file except in compliance with the License. You may obtain    
# a copy of the License at                                                   
#                                                                            
# http://www.apache.org/licenses/LICENSE-2.0                                 
#                                                                            
# Unless required by applicable law or agreed to in writing, software        
# distributed under the License is distributed on an "AS IS" BASIS,          
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   
# See the License for the specific language governing permissions and        
# limitations under the License.                                             
# -------------------------------------------------------------------------- 

dynamic_discover (){
    if [ -n "$SERVER" ]
    then
        TMPFILE=".search.$$.$RANDOM"
        ERRFILE=".error.$$.$RANDOM"
            
        grid-info-search -x -LLL -nowrap -p 2170 -h $SERVER -b $BASE \
                "(&(objectclass=GlueCluster)$HOSTFILTER)" GlueClusterUniqueID \
                > $TMPFILE 2>$ERRFILE

        if [ $? -eq 0 ]
        then
            HOSTNAMES=`grep GlueClusterUniqueID: $TMPFILE | awk '{print $2}'`

            for HOSTNAME in $HOSTNAMES
            do
                INFO="$INFO $HOSTNAME"
            done

            echo "DISCOVER - SUCCESS $INFO"
        else
            INFO=`cat $ERRFILE`
            echo "DISCOVER - FAILURE $INFO"
        fi
        
        rm -f $TMPFILE $ERRFILE
    else
        echo "DISCOVER - SUCCESS $INFO"
    fi
}

dynamic_monitor (){
    TMPFILE=".search.$$.$1.$RANDOM"
    ERRFILE=".error.$$.$1.$RANDOM"
    
    grid-info-search -x -LLL -h $2 > $TMPFILE 2> $ERRFILE
            
    if [ $? -eq 0 ]
    then
        CPU_MHZ=0; CPU_FREE=0; CPU_SMP=0; NODECOUNT=0; FREE_MEM_MB=0
        SIZE_MEM_MB=0; FREE_DISK_MB=0; SIZE_DISK_MB=0
        
        HOSTNAME=`grep GlueClusterUniqueID: $TMPFILE | awk -F": " '{print $2}' | head -1`
        OS_NAME=`grep GlueHostOperatingSystemName: $TMPFILE | awk -F": " '{print $2}' | head -1`
        OS_VERSION=`grep GlueHostOperatingSystemVersion: $TMPFILE | awk -F": " '{print $2}' | head -1`
        CPU_MODEL=`grep GlueHostProcessorModel: $TMPFILE | awk -F": " '{print $2}' | head -1`
        CPU_MHZ=`grep GlueHostProcessorClockSpeed: $TMPFILE | awk -F": " '{print $2}' | head -1`
        CPU_SMP=`grep GlueHostArchitectureSMPSize: $TMPFILE | awk -F": " '{print $2}' | tail -1`
        NODECOUNT=`grep GlueCEInfoTotalCPUs: $TMPFILE | awk -F": " '{print $2}' | tail -1`
        FREE_MEM_MB=`grep GlueHostMainMemoryRAMSize: $TMPFILE | awk -F": " '{print $2}' | head -1`
        SIZE_MEM_MB=`grep GlueHostMainMemoryRAMSize: $TMPFILE | awk -F": " '{print $2}' | head -1`
        LRMS_NAME=`grep GlueCEUniqueID: $TMPFILE | awk -F"/" '{print $2}' | awk -F- '{ORS=""; print $1; for (i=2;i<NF;i++) print "-" $i; print "\n"}' | tail -1`
        LRMS_TYPE=`grep GlueCEInfoLRMSType: $TMPFILE | awk -F": " '{print $2}' | tail -1`
        SE_HOSTNAME=(`grep GlueCEInfoDefaultSE: $TMPFILE | awk -F": " '{print $2}'`)

        grid-info-search -x -LLL -h $2 "(&(objectclass=GlueCE)$QUEUEFILTER)" > $TMPFILE 2> $ERRFILE

        if [ $? -eq 0 ]
        then
            QUEUE_NODECOUNT=0; QUEUE_FREENODECOUNT=0; QUEUE_MAXTIME=0; QUEUE_MAXCPUTIME=0
            QUEUE_MAXCOUNT=0; QUEUE_MAXRUNNINGJOBS=0; QUEUE_MAXJOBSINQUEUE=0

            QUEUE_NAME=(`grep GlueCEName: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_NODECOUNT=(`grep GlueCEInfoTotalCPUs: $TMPFILE | awk -F": " '{print $2}' | tail +1`)
            QUEUE_FREENODECOUNT=(`grep GlueCEStateFreeCPUs: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_MAXTIME=(`grep GlueCEPolicyMaxWallClockTime: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_MAXCPUTIME=(`grep GlueCEPolicyMaxCPUTime: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_MAXJOBSINQUEUE=(`grep GlueCEPolicyMaxTotalJobs: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_MAXRUNNINGJOBS=(`grep GlueCEPolicyMaxRunningJobs: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_STATUS=(`grep GlueCEStateStatus: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_PRIORITY=(`grep GlueCEPolicyPriority: $TMPFILE | awk -F": " '{print $2}'`)
            QUEUE_JOBWAIT=(`grep GlueCEStateWaitingJobs: $TMPFILE | awk -F": " '{print $2}'`)

            INFO=`echo "HOSTNAME=\"$HOSTNAME\" ARCH=\"i686\"" \
                "OS_NAME=\"$OS_NAME\" OS_VERSION=\"$OS_VERSION\"" \
                "CPU_MODEL=\"$CPU_MODEL\" CPU_MHZ=$CPU_MHZ CPU_FREE=0 CPU_SMP=$CPU_SMP" \
                "NODECOUNT=$NODECOUNT" \
                "SIZE_MEM_MB=$SIZE_MEM_MB FREE_MEM_MB=$FREE_MEM_MB" \
                "SIZE_DISK_MB=0 FREE_DISK_MB=0" \
                "FORK_NAME=\"jobmanager-fork\"" \
                "LRMS_NAME=\"$LRMS_NAME\" LRMS_TYPE=\"$LRMS_TYPE\"" \
                "SE_HOSTNAME=\"$SE_HOSTNAME\""`

            for ((j=0, i=0; i<${#QUEUE_NAME[@]}; i++,j++))
            do
                INFO=`echo "$INFO QUEUE_NAME[$j]=\"${QUEUE_NAME[$i]}\" QUEUE_NODECOUNT[$j]=${QUEUE_NODECOUNT[$i]}" \
                    "QUEUE_FREENODECOUNT[$j]=${QUEUE_FREENODECOUNT[$i]} QUEUE_MAXTIME[$j]=${QUEUE_MAXTIME[$i]}" \
                    "QUEUE_MAXCPUTIME[$j]=${QUEUE_MAXCPUTIME[$i]} QUEUE_MAXCOUNT[$j]=0" \
                    "QUEUE_MAXRUNNINGJOBS[$j]=${QUEUE_MAXRUNNINGJOBS[$i]} QUEUE_MAXJOBSINQUEUE[$j]=${QUEUE_MAXJOBSINQUEUE[$i]}" \
                    "QUEUE_DISPATCHTYPE[$j]=\"batch\" QUEUE_PRIORITY[$j]=\"${QUEUE_PRIORITY[$i]}\"" \
                    "QUEUE_STATUS[$j]=\"${QUEUE_STATUS[$i]}\""`
            done

            echo "MONITOR $1 SUCCESS $INFO"
        else
            INFO=`cat $ERRFILE`
            echo "MONITOR $1 FAILURE $INFO"                    
        fi            
    else
        INFO=`cat $ERRFILE`    
        echo "MONITOR $1 FAILURE $INFO"
    fi
    
    rm -f $TMPFILE $ERRFILE
}

BASE="mds-vo-name=local,o=grid"
HOSTFILTER=""
QUEUEFILTER=""

. gw_im_mad_common.sh

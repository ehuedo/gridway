/* -------------------------------------------------------------------------- */
/* Copyright 2002-2013, GridWay Project Leads (GridWay.org)                   */
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

package org.ggf.drmaa;

import java.util.*;

/** This class implements the GridWay specific methods. 
 *
 */

public class GridWayJobTemplate extends SimpleJobTemplate
{

	private long  				jobTemplatePointer;

	private java.util.Set 		optionalAttributeNames;
	
	private List					inputFiles;
	
	private List					outputFiles;
	
	private List					restartFiles;
		
	private String				rescheduleOnFailure; 
	
	private String				numberOfRetries;
	
	private String 				rank;

	private String 				requirements;
	
	private String				type = GridWaySession.GW_TYPE_SINGLE;
	
	private String 				np;
				
	public GridWayJobTemplate() 
	{
		super();
		this.setOptionalAttributeNames();
		this.attributeNames.addAll(this.optionalAttributeNames);
	}
	
	public GridWayJobTemplate(String name) 
	{		
		this();
		try
		{	
			this.setJobName(name);
		}
		catch (DrmaaException e)
		{
			System.out.println("Error:   " + e.getMessage());
		}
	}
	
	public  void setJobTemplatePointer(long ptr)
	{
		this.jobTemplatePointer = ptr;
	}
	
	
	/** This method set the attribute {@link org.ggf.drmaa.GridWayJobTemplate}.inputFiles. 
	 *  This attribute is an list of strings to refer to the input files of {@link #remoteCommand}.  
 	 *  Each vector entry is a pair of the form "source destination" filenames. 
 	 *  If the destination filename is missing, the source filename will be preserved 
 	 *  in the execution host. Input files (sources) ARE RELATIVE TO THE WORKING 
 	 *  DIRECTORY or can be a GSIFTP URL. Example: input_file[0]="param."GW_TASK_ID" param"
 	 *  will copy the local file param.2 (for task 2) as param in the remote working directory.
	 *  
	 *  @param inputFiles The input files to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setInputFiles(List inputFiles)
		throws DrmaaException
	{
		
		if (inputFiles == null)
			throw new InvalidAttributeValueException("The inputFiles are NULL");
		else
			this.inputFiles = new ArrayList<String>((ArrayList<String>) inputFiles);
	}
	
	/** This method set the attribute {@link org.ggf.drmaa.GridWayJobTemplate}.outputFiles. 
 	 *  This attribute is an array of strings to refer to the output files of {@link #remoteCommand}.  
 	 *  Each vector entry is a "source destination" filenames pair. If the
 	 *  destination filename is missing, the source filename will be preserved in the
 	 *  client host. Output files can be a GSIFTP URL. Example: 
 	 *  output_file[0]="binary binary."GW_ARCH will copy the output file "binary" to the
 	 *  client host with name binary.i686 (architecture of remote host is i686) 
 	 * 
	 *  @param outputFiles The output files to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setOutputFiles(List outputFiles)
		throws DrmaaException
	{
		if (outputFiles == null)
			throw new InvalidAttributeValueException("The outputFiles are NULL");
		else
			this.outputFiles = new ArrayList<String>((ArrayList<String>) outputFiles);	
	}
	
	/** This method set the attribute {@link GridWayJobTemplate}.restartFiles. 
 	 *  This attribute is an array of strings to refer to the re-start files generated by {@link #remoteCommand}.  
 	 *  Each vector entry is the name of a checkpointing file. Re-start files can be used to preserve the execution
 	 *  context (at the application level) of the remoteCommand on job 
 	 *  migration or stop/resume actions.
	 
	 *  @param restartFiles The restart files to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setRestartFiles(List restartFiles)
		throws DrmaaException
	{
		if (restartFiles == null)
			throw new InvalidAttributeValueException("The restartFiles are NULL");
		else
		{
			this.restartFiles =  new ArrayList<String>((ArrayList<String>) restartFiles);
		}
	}
	
	/** This method set the attribute {@link GridWayJobTemplate}.rescheduleOnFailure. 
	 *  This attribute is a String to refer to the ON_FAILURE GridWay scheduler
 	 *  parameter. If set to "yes" GridWay will reschedule the job  
 	 *  after retrying execution on a given host drmaa_gw_number_of_retries times.
 	 *  Values are "yes" or "no". Default value for this attribute is "no".
 	 *
	 *  @param onFailure The boolean reschedule on failure value to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */		
	public  void setRescheduleOnFailure(String onFailure)
		throws DrmaaException
	{
		if (onFailure == null)
			throw new InvalidAttributeValueException("The onFailure attribute is NULL");	
		else
			this.rescheduleOnFailure = new String(onFailure);
	}
	
	/** This method set the attribute {@link GridWayJobTemplate}.numberOfRetries. 
	 *	
	 *  This attribute is a String to refer to the NUMBER_OF_RETRIES GridWay scheduler
 	 *  parameter, the number of times to retry the execution on a given host.
 	 *  Default value is 3.
	 *  @param numberOfRetries The number of retries to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setNumberOfRetries(String numberOfRetries)
		throws DrmaaException
	{
		if (numberOfRetries == null)
			throw new InvalidAttributeValueException("The numberOfRetries attribute is NULL");	
		else
			this.numberOfRetries = new String(numberOfRetries);	
	}

	
	/** This method set the attribute {@link GridWayJobTemplate}.rank. 
 	 *  This attribute is a String to refer to the RANK job template parameter.
 	 *  The RANK is a mathematical expression evaluated for each
 	 *  candidate host (those for which the REQUIREMENTS expression is true).
 	 *  Those candidates with higher ranks are used first to execute your jobs. Example: 
 	 *  "(CPU_MHZ * 2) + FREE_MEM_MB;" (NOTE: Must end with ';')
	 *
	 *  @param rank The rank to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setRank(String rank)
		throws DrmaaException
	{
		if (rank == null)
			throw new InvalidAttributeValueException("The rank attribute is NULL");	
		else
			this.rank = new String(rank);	
	}

	/** This method set the attribute {@link GridWayJobTemplate}.requirements. 
 	 *  This attribute is a String to refer to the REQUIREMENTS job template parameter.
 	 *  The REQUIREMENTS is a boolean expression evaluated for each host in the 
 	 *  Grid, if it is true the host will be considered to submit the job. 
 	 *  Example:"ARCH = "i686" & CPU_MHZ > 1000;" (NOTE: Must end with ';')
	 *
	 *  @param requirements The requirements to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setRequirements(String requirements)
		throws DrmaaException
	{
		if (requirements == null)
			throw new InvalidAttributeValueException("The requirements attribute is NULL");	
		else
			this.requirements = new String(requirements);	
	}
	
	/** This method set the attribute {@link GridWayJobTemplate}.type. 
 	 *  This attribute is a String to refer to the TYPE  job template parameter.
 	 *  The TYPE is the type of the job. Possible values are "single" (default), 
 	 *  and "mpi", with similar behaviour to that of GRAM jobs. 
	 *
	 *  @param type The type to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setType(String type)
		throws DrmaaException
	{
		if (type == null)
			throw new InvalidAttributeValueException("The type attribute is NULL");	
		else
			this.type = new String(type);	
	}
	
	
	/** This method set the attribute {@link GridWayJobTemplate}.np. 
 	 *  This attribute is a String to refer to the NP  job template parameter.
 	 *  The NP  is a attribute to refer to the number of process requested by a MPI job. 
	 *
	 *  @param np The number of process to set
 	 *
	 *  @throws InvalidAttributeValueException
 	 */	
	public  void setNp(String np)
		throws DrmaaException
	{
		if (np == null)
			throw new InvalidAttributeValueException("The np attribute is NULL");	
		else
			this.np = new String(np);	
	}

	
	
	public  long getJobTemplatePointer()
	{
		return this.jobTemplatePointer;
	}
	
	/** This method get the attribute {@link GridWayJobTemplate}.inputFiles. 
	 *  This attribute is an array of strings to refer to the input files of {@link #remoteCommand}.  
 	 *  Each vector entry is a pair of the form "source destination" filenames. 
 	 *  If the destination filename is missing, the source filename will be preserved 
 	 *  in the execution host. Input files (sources) ARE RELATIVE TO THE WORKING 
 	 *  DIRECTORY or can be a GSIFTP URL. Example: input_file[0]="param."GW_TASK_ID" param"
 	 *  will copy the local file param.2 (for task 2) as param in the remote working directory.
	 *  @return A String array with the drmaa_v_gw_input_files value
 	 *
 	 */
	public  List getInputFiles()
	{
		return this.inputFiles;
	}
	
	/** This method get the attribute {@link GridWayJobTemplate}.outputFiles. 
 	 *  This attribute is an array of strings to refer to the output files of {@link #remoteCommand}.  
 	 *  Each vector entry is a "source destination" filenames pair. If the
 	 *  destination filename is missing, the source filename will be preserved in the
 	 *  client host. Output files can be a GSIFTP URL. Example: 
 	 *  output_file[0]="binary binary."GW_ARCH will copy the output file "binary" to the
 	 *  client host with name binary.i686 (architecture of remote host is i686)  	 
 	 *
	 *  @return A String array with the drmaa_v_gw_output_files value
 	 *
 	 */
	public  List getOutputFiles()
	{
		return this.outputFiles;
	}
	
	/** This method get the attribute {@link GridWayJobTemplate}.restart_files. 
 	 *  This attribute is an array of strings to refer to the re-start files generated by {@link #remoteCommand}.  
 	 *  Each vector entry is the name of a checkpointing file. Re-start files can be used to preserve the execution
 	 *  context (at the application level) of the REMOTE_COMMAND on job 
 	 *  migration or stop/resume actions.
	 *
	 *  @return A String array with the drmaa_v_gw_restart_files value
 	 *
 	 */
	public  List getRestartFiles()
	{
		return this.restartFiles;
	}
		
	/** This method get the attribute {@link GridWayJobTemplate}.rescheduleOnFailure. 
 	 *  This attribute is a String to refer to the ON_FAILURE GridWay scheduler
 	 *  parameter. If set to "yes" GridWay will reschedule the job  
 	 *  after retrying execution on a given host drmaa_gw_number_of_retries times.
 	 *  Values are "yes" or "no". Default value for this attribute is "no".
 	 * 
	 *  @return A String array with the drmaa_gw_reschedule_on_failure value
 	 *
 	 */
	public  String getRescheduleOnFailure()
	{
		return this.rescheduleOnFailure;	
	}
	
	/** This method get the attribute {@link GridWayJobTemplate}.numberOfRetries. 
 	 *  This attribute is a String to refer to the NUMBER_OF_RETRIES GridWay scheduler
 	 *  parameter, the number of times to retry the execution on a given host.
 	 *  Default value is 3. 
	 *
	 *  @return A String array with the numberOfRetries value
 	 *
 	 */
	public  String getNumberOfRetries()
	{
		return this.numberOfRetries;	
	}
	
	
	/** This method get the attribute {@link GridWayJobTemplate}.rank. 
 	 *  This attribute is a String to refer to the REQUIREMENTS job template parameter.
 	 *  The REQUIREMENTS is a boolean expression evaluated for each host in the 
 	 *  Grid, if it is true the host will be considered to submit the job. 
 	 *  Example:"ARCH = "i686" & CPU_MHZ > 1000;" (NOTE: Must end with ';')
	 *  @return A String array with the rank value
 	 *
 	 */
	public  String getRank()
	{
		return this.rank;	
	}

	/** This method get the attribute {@link GridWayJobTemplate}.requirements. 
 	 *  This attribute is a String to refer to the RANK job template parameter.
 	 *  The RANK is a mathematical expression evaluated for each
 	 *  candidate host (those for which the REQUIREMENTS expression is true).
 	 *  Those candidates with higher ranks are used first to execute your jobs. Example: 
 	 *  "(CPU_MHZ * 2) + FREE_MEM_MB;" (NOTE: Must end with ';')
	 * 
	 *  @return A String array with the requirements value
 	 *
 	 */
	public  String getRequirements()
	{
		return this.requirements;	
	}
	
	/** This method get the attribute {@link GridWayJobTemplate}.type. 
 	 *  This attribute is a String to refer to the TYPE  job template parameter.
 	 *  The TYPE is the type of the job. Possible values are "single" (default), 
 	 *  and "mpi", with similar behaviour to that of GRAM jobs. 
	 *
	 *  @return A String  with the type value
 	 *
 	 */	
	public  String  getType()
	{
		return	this.type;	
	}
	
	
	/** This method get the attribute {@link GridWayJobTemplate}.np. 
 	 *  This attribute is a String to refer to the NP  job template parameter.
 	 *  The NP  is a attribute to refer to the number of process requested by a MPI job. 
	 *
	 *  @return A String  with the np value
 	 *
 	 */	
	public  String getNp()
	{
		return 	this.np;	
	}	
	
	private void setOptionalAttributeNames()
	{
		this.optionalAttributeNames = new  java.util.HashSet();
		
		optionalAttributeNames.add("gw_input_files");
		optionalAttributeNames.add("gw_output_files");
		optionalAttributeNames.add("gw_restart_files");
		optionalAttributeNames.add("gw_reschedule_on_failure");
		optionalAttributeNames.add("gw_number_of_retries");
		optionalAttributeNames.add("gw_rank");
		optionalAttributeNames.add("gw_requirements");	
		optionalAttributeNames.add("gw_type");
		optionalAttributeNames.add("gw_np");	
	}
	
}
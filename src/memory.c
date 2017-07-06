#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int memory (int k, int f, int q, int max)
	{
	int i, j, p_number, pid, on_memory, PF_k1 = 0, PF_k2 = 0, PF = 0, disk_write = 0, disk_read = 0, trace_entries = 0;
	char p_number_str[5], p_oper[1], line[256];
	char *token;
	int **IPT;	

	
	/* Dynamic memory allocate for Inverted Page Table */
	if ((IPT = malloc(f * sizeof(int*))) == NULL)
		{
		printf("Error allocating memory\n");
		return -1;
		}
		
	for (i = 0 ; i < f ; i++)
		{
		if ((IPT[i] = malloc(4 * sizeof(int))) == NULL)
			{
			printf("Error allocating memory\n");
			return -1;
			}
		
		/*  Initialization of valid bit to 0  */
		IPT[i][3] = 0;			
		}

	/* Open first trace files */	
	FILE* process1 = fopen("bzip.trace", "r"); 
	
	if (process1 == NULL)
		{
		printf("Error opening the trace file\n");
		return -2;
		}
	
	/* Open second trace files */	
	FILE* process2 = fopen("gcc.trace", "r"); 
	
	if (process2 == NULL)
		{
		printf("Error opening the trace file\n");
		return -2;
		}
	
	/* Loop while trace_entries match max */
	while(1)
		{			
		/* Examine traces of q-size block from first process */
		for (i = 0 ; i < q ; i++)
			{
			/* Read one line of first trace file and update p_number, p_oper, pid */
			pid = 1;
			fgets(line, sizeof(line), process1);
			
			token = strtok(line, " /t");		
			strncpy(p_number_str, token, 5);
			p_number_str[5] = 0; // Null terminate destination
			p_number = (int)strtol(p_number_str, NULL, 16);		
									
			token = strtok(NULL, " /t");
			strcpy(p_oper, token);
			p_oper[1] = 0; // Null terminate destination
			
			on_memory = 0;
			
			/* Search IPT for process with p_number */
			for (j = 0 ; j < f ; j++)
				{
				if (IPT[j][3] != 0)
					{	
					if (IPT[j][0] == pid && IPT[j][1] == p_number)	
						{
						if (!strcmp(p_oper, "W"))
							IPT[j][2] = 1;	// Set it dirty
							
						on_memory = 1;
						}
					}	
				}
			
			/* Trace not on IPT, page fault occurs*/
			if (on_memory == 0)
				{
				PF_k1++;			// block page fault counter
				PF++;				// statistic total page fault counter
				disk_read++;

				if (PF_k1 > k)
					{
					/* Execute PWF for traces with pid */
					for (j = 0 ; j < f ; j++)
						{
						if (IPT[j][0] == pid)
							{	
							if (IPT[j][2] == 1)	
								disk_write++;
								
							IPT[j][3] = 0;
							}	
						}				
					PF_k1 = 1;				
					}
					
				/* Update IPT with new trace */
				for (j = 0 ; j < f ; j++)
					{
					if (IPT[j][3] == 0 && (IPT[j][0] == pid || IPT[j][0] == 0)){	
						IPT[j][0] = pid;
						IPT[j][1] = p_number;	
						IPT[j][3] = 1;
						
						if (!strcmp(p_oper, "W"))
							IPT[j][2] = 1;	// Set it dirty
						else
							IPT[j][2] = 0;	// Set it clean

						break;
						}	
					}								
				}
			
			trace_entries++;
			
			/* Check if we already examine max entries from both trace files */
			if (trace_entries == max)
				{
				/* Execute PWF for whole IPT at exit and update statistic variables */
				for (j = 0 ; j < f ; j++)
					{				
					if (IPT[j][3] != 0)
						{
						if (IPT[j][2] == 1)	
							disk_write++;	

						IPT[j][3] = 0;	
						}
					}		
					
				printf("Frames wrote on disc: %d\n", disk_write);
				printf("Frames read from disc: %d\n", disk_read);
				printf("Page faults: %d\n" , PF);
				printf("Trace entries examined from files: %d\n", trace_entries);
				printf("Memory frames: %d\n", f);
			
				fclose(process1);
				fclose(process2);
				
				for (i = 0 ; i < f ; i++)
					{
					free(IPT[i]);
					}
				free(IPT);
				
				return 0;
				}
			} 	
		
		
		/* Examine traces of q-size block from second process */	
		for (i = 0 ; i < q ; i++)
			{
			/* Read one line of second trace file and update p_number, p_oper, pid */
			pid = 2;
			fgets(line, sizeof(line), process2);
			
			token = strtok(line, " /t");		
			strncpy(p_number_str, token, 5);
			p_number_str[5] = 0; // Null terminate destination
			p_number = (int)strtol(p_number_str, NULL, 16);		
									
			token = strtok(NULL, " /t");
			strcpy(p_oper, token);
			p_oper[1] = 0; // Null terminate destination
			
			on_memory = 0;
			
			/* Search IPT for process with p_number */
			for (j = 0 ; j < f ; j++)
				{
				if (IPT[j][3] != 0)
					{	
					if (IPT[j][0] == pid && IPT[j][1] == p_number)	
						{
						if (!strcmp(p_oper, "W"))
							IPT[j][2] = 1;	// Set it dirty
						
						on_memory = 1;
						}
					}	
				}
			
			/* Trace not on IPT, page fault occurs */
			if (on_memory == 0)
				{
				PF_k2++;			// block page fault counter
				PF++;				// statistic total page fault counter
				disk_read++;

				if (PF_k2 > k)
					{
					// Execute PWF
					for (j = 0 ; j < f ; j++)
						{
						if (IPT[j][0] == pid)
							{	
							if (IPT[j][2] == 1)	
								disk_write++;

							IPT[j][3] = 0;
							}	
						}				
					PF_k2 = 1;				
					}
					
				/* Update IPT with new trace */
				for (j = 0 ; j < f ; j++)
					{
					if (IPT[j][3] == 0 && (IPT[j][0] == pid || IPT[j][0] == 0)){	
						IPT[j][0] = pid;
						IPT[j][1] = p_number;	
						IPT[j][3] = 1;
						
						if (!strcmp(p_oper, "W"))
							IPT[j][2] = 1;	// Set it dirty
						else
							IPT[j][2] = 0;	// Set it clean

						break;
						}	
					}								
				}
			
			trace_entries++;
			
			/* Check if we already examine max entries from both trace files */
			if (trace_entries == max)
				{
				/* Execute PWF for whole IPT at exit and update statistic variables */
				for (j = 0 ; j < f ; j++)
					{				
					if (IPT[j][3] != 0)
						{
						if (IPT[j][2] == 1)	
							disk_write++;	
						
						IPT[j][3] = 0;	
						}
					}	
					
				printf("Frames wrote on disc: %d\n", disk_write);
				printf("Frames read from disc: %d\n", disk_read);
				printf("Page faults: %d\n" , PF);
				printf("Trace entries examined from files: %d\n", trace_entries);
				printf("Memory frames: %d\n", f);
			
				fclose(process1);
				fclose(process2);
				
				for (i = 0 ; i < f ; i++)
					{
					free(IPT[i]);
					}
				free(IPT);
				
				return 0;
				}				
			} 
		}
	}
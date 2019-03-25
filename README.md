
## Overview

In computer operating systems, virtual memory is a management technique to handle the computer's primary memory. A page, memory page or virtual page is a fixed-length contiguous block of virtual memory and in similar a page frame is the smallest fixed-length contiguous block of physical memory. Virtual memory maps the virtual addresses (organized in pages) used by a program into physical addresses (organized in page frames) in computer memory, using a page table, which is a data structure to store this mapping.


![Inverted page table](https://github.com/chanioxaris/virtual-memory/blob/master/img/IPT.png)

This program simulates the function of an operation system that uses paging for virtual memory management, alongside with Inverted page table and Flush When Full (FWF) as a page replacement algorithm. Round-robin algorithm is used for scheduling between the reference traces of two processes.

### Inverted page table (IPT)

Inverted page table is a advanced type of page table. In contrast with classical (where each process has it's own), inverted page table is global and maintained by the operating system for all the processes. There is just one page table in the entire system, implying that additional information needs to be stored in the page table to identify page table entries corresponding to each process. 
<br />
The page table stores the frame number into an array indexed by page number: given the page number, the frame number is achieved by a simple indexed load. An inverted page table stores the page number in an array indexed by frame number. Given the page number, you search for the entry with that page number: the entry number specifies the frame.


### Flush When Full (FTW)

Flush When Full algorithm allows up to k page faults to occur for a single process. When the k+1 page fault appears, all pages from the specific process in page table are evicted (flush).


### Round-robin algorithm (RR)
Round-robin (RR) is one of the algorithms employed by process schedulers. To schedule processes fairly, a round-robin scheduler generally employs time-sharing, giving each job a time slot or quantum (its allowance of CPU time), and interrupting the job if it is not completed by then. The job is resumed next time a time slot is assigned to that process. The scheduler selects the first process in the ready queue to execute, thus handling all processes without priority.


## Statistics

After the simulation is over, some statistics are printed which are: 
- Number of Page Faults occured 
- Number of writes back on disk for the dirty traces 
- Number of reads from disk
- Number of total traces 

The below table includes the results of the simulation for different numbers of input argument k (FWF parameter)

|         | Page Faults | PT Frames  | Reads | Writes | Traces | 
| :------ | :---------: | :--------: | :---: | :----: | :----: |
| k = 10  |     817     |     20     |  817  |   506  |  2000  |
| k = 25  |     582     |     50     |  582  |   361  |  2000  |  
| k = 50  |     496     |     100    |  496  |   318  |  2000  |  
| k = 100 |     439     |     200    |  439  |   280  |  2000  |  
| k = 250 |     399     |     500    |  399  |   255  |  2000  |  


## Compile

`./makefile`

## Usage

`./simulation -k [parameter of FWF algorithm] -q [round-robin quantum] -m [number of traces to examine]`

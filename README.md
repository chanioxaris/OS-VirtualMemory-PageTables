
## Overview

In computer operating systems, virtual memory is a management technique to handle the computer's primary memory. A page, memory page or virtual page is a fixed-length contiguous block of virtual memory and in similar a page frame is the smallest fixed-length contiguous block of physical memory. Virtual memory maps the virtual addresses (organized in pages) used by a program into physical addresses (organized in page frames) in computer memory, using a page table, which is a data structure to store this mapping.

<br />
This program simulates the function of an operation system that uses paging for virtual memory management, alongside with Inverted age table and Flush When Full (FWF) as a page replacement algorithm. Round-robin algorithm is used for scheduling between the reference traces of two processes.

### Inverted page table

Inverted page table is a 

### Flush When Full

When the fast memory is full, a request for a page not in fast memory causes the cache to be cleared.
All pages from the same process are evicted (flush), when the k+1 distinct page request arrives.



### Round-robin algorithm



## Statistics

After the simulation is over, some statistics are printed which are: 1) Number of Page Faults occured 2) Number of writes back on disk for the dirty traces 3) Number of reads from disk 4) Number of total traces 

## Compile

`./makefile`

## Usage

`./simulation -k [parameter of FWF algorithm] -q [round-robin quantum] -m [number of traces to examine]`


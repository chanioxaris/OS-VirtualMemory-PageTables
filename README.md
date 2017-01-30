# OS-VirtualMemory-PageTables

A simple simulator for Virtual Memory and Inverted Page Table. 
Reads 2 files(bzip.trace and gcc.trace) which include traces from 2 program and runs the simulator using Round Robin.

For scheduling uses the FWF( Flush When Full) algorithm. 
When the fast memory is full, a request for a page not in fast memory causes the cache to be cleared.
All pages from the same process are evicted (flush), when the k+1 distinct page request arrives.

Three parameters are mandatory for the program. 1) "-k" which is the parameter of FWF algorithm 2) "-q" the quantum of Round Robin 3) "-m" how many traces to examine in total

After the simulation is over, some statistics are printed which are: 1) Number of Page Faults occured 2) Number of writes back on disk for the dirty traces 3) Number of reads from disk 4) Number of total traces 

Makefile also included.

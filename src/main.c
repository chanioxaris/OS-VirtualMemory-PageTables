#include <stdio.h>
#include <stdlib.h>


int memory(int, int, int, int);

int main(int argc, char* argv[])
	{
	int i, k, q, max;

	if (argc == 7)
		{
		for (i = 1 ; i < (argc-1) ; i++)
			{
			if (!strcmp(argv[i], "-k"))
				{
				k = atoi(argv[++i]);
				continue;
				}
			if (!strcmp(argv[i], "-q"))
				{
				q = atoi(argv[++i]);
				continue;
				}
			if (!strcmp(argv[i], "-m"))
				{
				max = atoi(argv[++i]);
				continue;
				}
			printf("Wrong input arguments! \n");
			return -1;
			}
		}
	else
		{
		printf("Wrong input arguments! \n");
		return -1;	
		}
	
	memory(k, 2*k, q, max);
		
	return 0;
	}
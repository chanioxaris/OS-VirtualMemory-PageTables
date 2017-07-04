CC = gcc

PROG = simulation
SRCS = main.c memory.c

OBJS = $(SRCS:.c=.o)

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) -lpthread

clean :
	rm -f $(OBJS) $(PROG)

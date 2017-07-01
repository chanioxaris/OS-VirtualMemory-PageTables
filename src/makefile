CC = gcc

PROG = askisi2
SRCS = main.c memory.c

OBJS = $(SRCS:.c=.o)

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) -lpthread

clean :
	rm -f $(OBJS) $(PROG)
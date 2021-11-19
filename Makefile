CC = gcc
LFLAGS = -Wall -pedantic-errors
CFLAGS = $(LFLAGS) -c

wc: wc.o 
	$(CC) $(LFLAGS) -o wc wc.o

head: head.o 
	$(CC) $(LFLAGS) -o head head.o

tail: tail.o 
	$(CC) $(LFLAGS) -o tail tail.o

env: env.o 
	$(CC) $(LFLAGS) -o env env.o

wc.o: wc.c 
	$(CC) $(CFLAGS) wc.c

head.o: head.c 
	$(CC) $(CFLAGS) head.c

tail.o: tail.c 
	$(CC) $(CFLAGS) tail.c

env.o: env.c 
	$(CC) $(CFLAGS) env.c

clean:
	rm -f head
	rm -f tail
	rm -f *.o

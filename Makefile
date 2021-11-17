CC = gcc
LFLAGS = -Wall -pedantic-errors
CFLAGS = $(LFLAGS) -c

wc: wc.o 
	$(CC) $(LFLAGS) -o wc wc.o

head: head.o 
	$(CC) $(LFLAGS) -o head head.o

env: env.o 
	$(CC) $(LFLAGS) -o env env.o

true: true.o 
	$(CC) $(LFLAGS) -o true true.o

false: false.o 
	$(CC) $(LFLAGS) -o false false.o

wc.o: wc.c 
	$(CC) $(CFLAGS) wc.c

head.o: head.c 
	$(CC) $(CFLAGS) head.c

env.o: env.c 
	$(CC) $(CFLAGS) env.c

true.o: true.c 
	$(CC) $(CFLAGS) true.c

false.o: false.c 
	$(CC) $(CFLAGS) false.c

clean:
	rm -f true false head env wc 
	rm -f *.o

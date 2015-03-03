CC = $gcc
CCFLAGS = -g -Wall -m32

all: sl

sl: libsl.a main.o
  $(CC) -m32 -o $@ main.o -L. -lsl

libsl.a: sorted-list.o
  ar rv libsl.a sorted-list.o
  
sorted-list.o: sorted-list.c sorted-list.h
  $(CC) $(CCFLAGS) -c sorted-list.c

main.o: main.c
  $(CC) $(CCFLAGS) -c main.c
  
clean:
  -rm -rf *.a *.o sl

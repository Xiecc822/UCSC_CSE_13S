CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -Wstrict-prototypes
IOARCH := $(shell uname -m)

ifeq ($(IOARCH), aarch64)
IO = io-aarch64.a
else ifeq ($(IOARCH), x86_64)
IO = io-x86_64.a
endif

.PHONY: all clean fromat 

all: huff pqtest nodetest bwtest

huff: huff.c bitwriter.c pq.c node.c
	$(CC) $(CFLAGS) $^ -o $@ $(IO) 
	
pqtest: pqtest.c bitwriter.c node.c pq.c 
	$(CC) $(CFLAGS) $^ -o $@ $(IO) 
	
nodetest: nodetest.c node.c 
	$(CC) $(CFLAGS) $^ -o $@ 
	
bwtest: bwtest.c bitwriter.c 
	$(CC) $(CFLAGS) $^ -o $@ $(IO)  
	

format: 
	clang-format -i bitwriter.c bitwriter.h huff.c io.h node.c node.h pq.c pq.h  pqtest.c nodetest.c bwtest.c
	
clean: 
	rm -f huff pqtest nodetest bwtest *.o

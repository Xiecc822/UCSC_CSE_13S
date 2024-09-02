EXEC = tsp
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)


CC = clang
debug:   CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g
release: CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS = -lm

all: $(EXEC)

$(EXEC): $(OBJECTS)
		$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o : %.c
		$(CC) $(CFLAGS) -c $<

tidy: 
		rm -rf $(OBJECTS)

clean: tidy
		rm -rf $(EXEC)

format:
		clang-format -i -style=file *.[ch]

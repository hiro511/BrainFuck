PROGRAM = bf
CC = clang
CFLAGS = -Wall -O2
RM = rm

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(PROGRAM)

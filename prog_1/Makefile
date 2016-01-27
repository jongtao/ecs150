CC=cc
CFLAGS=-Wall -g

all: pipetest AlrmTest directory_traverse_breadth_first process_tree smallsh warm

pipetest:
	@echo $@ not yet written

AlrmTest: AlrmTest.c
	$(CC) $(CFLAGS) $< -o $@

directory_traverse_breadth_first: directory_traverse_breadth_first.c
	$(CC) $(CFLAGS) $< -o $@

process_tree: process_tree.c
	$(CC) $(CFLAGS) $< -o $@

smallsh: smallsh.c smallsh.h
	$(CC) $(CFLAGS) $< -o $@

warm: warm.c
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean
clean:
	rm -f *.o core pipetest \
	AlrmTest directory_traverse_breadth_first process_tree smallsh warm

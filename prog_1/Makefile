CC=cc
CFLAGS=-Wall

all: pipetest AlrmTest directory_traverse_breadth_first process_tree smallsh warm

pipetest:
	@echo $@ not yet written

AlrmTest:
	@echo $@ not yet written

directory_traverse_breadth_first:
	@echo $@ not yet written

process_tree: process_tree.c
	$(CC) $(CFLAGS) $< -o $@

smallsh: smallsh.c smallsh.h
	$(CC) $(CFLAGS) $< -o $@

warm: warm.c
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean
clean:
	rm -f *.o core

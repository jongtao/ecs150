CC=cc
CFLAGS=-Wall -g

all: pipe_test AlrmTest directory_traverse_breadth_first process_tree smallsh warm

pipe_test: pipe_test.c
	$(CC) $(CFLAGS) $< -o $@

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
	rm -f *.o core pipe_test \
	AlrmTest directory_traverse_breadth_first process_tree smallsh warm

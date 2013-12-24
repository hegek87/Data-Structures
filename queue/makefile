all:
	gcc -c -g -Wall queue.c
	mv queue.o ./objects
	rm -f queue.o
	gcc -c -g -Wall ../double_linked_list/double_linked_list.c
	mv double_linked_list.o ../double_linked_list/objects
	rm -f double_linked_list.o
	gcc -o ./objects/queue ./objects/queue.o ../double_linked_list/objects/double_linked_list.o

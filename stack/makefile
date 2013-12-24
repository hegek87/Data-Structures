all:
	gcc -c -g -Wall stack.c
	mv stack.o ./objects
	rm -f stack.o
	gcc -c -g -Wall ../double_linked_list/double_linked_list.c
	mv double_linked_list.o ../double_linked_list/objects
	rm -f double_linked_list.o
	gcc -o ./objects/stack ./objects/stack.o ../double_linked_list/objects/double_linked_list.o

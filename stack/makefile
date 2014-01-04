all:
	gcc -c -g -Wall stack.c
	gcc -c -g -Wall ~/code/csrc/Data-Structures/double_linked_list/double_linked_list.c
	
	mv *.o ./objects
	gcc ./objects/stack.o ./objects/double_linked_list.o -o ./objects/stack
	rm -f *.o

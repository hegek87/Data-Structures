all:
	gcc -c -g -Wall hash_table.c 
	gcc -c -g -Wall ../double_linked_list/double_linked_list.c
	
	gcc double_linked_list.o hash_table.o -o ./objects/hash_table
	mv *.o ./objects

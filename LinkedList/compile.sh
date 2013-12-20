#!/bin/bash
# Script to compile and execute a c program in one step.

# Compile the program with -o option to specify the name of the binary
gcc -g -Wall linked_list.c -o ./objects/linked_list 

# If there were no compilation errors, run the program
if [[ $? -eq 0 ]]; then
        ./objects/linked_list
fi

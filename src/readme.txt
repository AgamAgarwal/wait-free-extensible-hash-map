Files included
	Node.{h,c}pp
		Definition for abstract class Node
	DataNode.{h,c}pp
		Definition for class DataNode
	ArrayNode.{h,c}pp
		Definition for class ArrayNode
	utils.{h,c}pp
		File containing common utility functions
	HashMap.{h,c}pp
		Definition for abstract class HashMap
	WFEHashMap.{h,c}pp
		Definition for class WFEHashMap - Wait-free Extensible HashMap
	LBEHashMap.{h,c}pp
		Definition for class LBEHashMap - Lock-based Extensible HashMap
	main.cpp
		File containing code to use the above classes to test Wait-free and
		Lock-based Extensible HashMap implementations
	Makefile
		File containing the commands to compile the source code and setup
		required directory for output
	in
		Sample input file

Compilation
	To compile the source code, fire up a terminal, navigate to the directory
	containing the codes and type the following:
		make

	This will generate the compiled object and executable files and will also
	create a directory named 'output/' which will contain the output files.

Execution
	To run the program, create an input file with the following parameters
		<number of putter threads> <number of getter threads> <number of remover threads> <number of iterations> <mu>

	A sample input file 'in' is provided with this file.
	To run the program, type the following
		./main <input file>
	or
		./main
	Note: When using the second method (without command line args) the program
	will ask you to enter the name of the file containing the input parameters.

	After the program's execution is completed, outputs for different threads
	will be created in the directory 'output/'.

Important Note
	The source code was test on Ubuntu 14.04 and was found to execute properly.
	Its behavior might differ on other systems.

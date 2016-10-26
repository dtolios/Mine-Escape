# Mine Escape

### This project is simply to help level-up my understanding of data structures and algorithms.

## Overview
You are an adventurous gold miner. However, in your avarice you’ve ignored several safe­ tunneling practices, and a recent earthquake has left you trapped! Luckily, out of paranoia, you always carry ridiculous quantities of dynamite sticks with you. You need to blast your way out and make the most of each dynamite stick by blasting the piles of rubble which take the fewest sticks to destroy. Will you be able to find your way out before you run out of dynamite?

## Command Line Input
MineEscape takes the following case-sensitive command line options:
* -h,--help
  * Print a description of your executable and exit(0). ● -c,--container
  * Required option. Changes the type of priority queue that your implementation uses at runtime. Must be one of BINARY,POOR_MAN,SORTED,or PAIRING.
  * NOTE: It is a violation of the honor code to misrepresent your code or submit code for a grade that uses a priority queue implementation different from what is asked. (i.e., if you don’t finish a particular implementation, your code should immediately terminate when we invoke it with that container). However, for testing purposes you may find it useful to submit preliminary versions that do not conform to this. This is allowed as long as you clearly place a comment near the start of your main function that indicates this is only a test version not intended for final grading.
* -v,--verbose N
  * An optional flag that indicates the program should print additional output statistics. This option takes a required argument, N, which is an integer value greater than 0.

*MineEscape also takes a mandatory file argument (whenever the help option is not specified), ‘MINEFILE’, which should always be given as the very last argument on the command line. If ‘MINEFILE’is not specified on the command line, an error message is printed to cerr and 1 is returned to main.

#### Examples of legal command lines:
* `./MineEscape --container BINARY infile.txt`
* `./MineEscape --verbose 15 -c PAIRING infile.txt > outfile.txt`

#### Examples of illegal command lines:
* `./MineEscape --container BINARY < infile.txt`
  * No input file was given on command line. We are not reading input from standard input with input redirection in this project.
* `./MineEscapeinfile.txt`
  * No container type was specified. Container type is a required option.

Command line error handling matches the default behavior of getopt.
Properly formatted input is required for this project. 

FILES: voting.c, borda.h, instant_runoff.h, pairwise_comparison.h, schulze_beatpath.h
AUTHORS: Sasha Bakker, Shoale Badr
DATE: 11/18/21
COMPILER: GCC (Command Line)
OS: Windows 10

DESCRIPTION
------------
The purpose of this project is to implement different voting methods 
for deciding the winner of an election. Note that not every method 
results in the same winner.

RUNNING THE PROGRAM
-------------------
The file `voting.c` requires the header files `stdio.h`, `string.h`, 
`stdlib.h`, and `limits.h` from the standard C library.

It also requires the header files `borda.h`, `instant_runoff.h`,
`pairwise_comparison.h`, and `schulze_beatpath.h` to be saved in
the same folder as `voting.c`.

To compile `voting.c`, type `gcc -o voting voting.c` in the console.

To run the code and receive an output, type `./voting {filename.txt} {d}`.
The string {filename.txt} must be the name of a text file with voting data
that is saved in the same folder as `voting.c`. An error will be thrown 
if a file name is not included. The string {d} is the letter "d". This is
optional, and, if input, it displays the results in greater detail.

The output of the program will appear in the console.

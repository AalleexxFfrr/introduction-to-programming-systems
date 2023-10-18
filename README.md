# Project 1 - Text Processing

## Motivation

Imagine a virtual keyboard in a car's dashboard navigation system. The navigation system has a database of addresses and expects the user to input via a virtual keyboard. To make the input easier for the user, only specific keys are enabled on the keyboard at any given moment - those keys that, when used, would still lead to a known address. For example, if the navigation system knows the cities of Brno, Beroun, and Bruntál, and the user has already entered the letters "BR," then only the "N" key (leading to "Brno") and the "U" key (leading to "Bruntál") will be enabled on the navigation keyboard.

## Project Description

The goal of this project is to create a program that emulates the algorithm for determining which keys are enabled and disabled on the virtual keyboard of the navigation system. The program takes as input a list of known addresses and a user-entered string, and it outputs the characters that should be enabled on the keyboard.

## Detailed Specification

Implement the program in a single source file, `keyfilter.c`. Input data will be read from standard input (stdin), and output will be printed to standard output (stdout).

## Compilation of the Source File

Compile the program using the following arguments:

~~~shell
$ gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter
~~~

## Usage Syntax

~~~shell
./keyfilter ADDRESS
~~~

If the program is run without arguments, it takes the address as an empty string.

## Implementation Details
### Input Address Database

The address database is textual data where each line represents one address. Each line contains a maximum of 100 characters. The list of addresses is unordered. The program must support at least 42 addresses.

### Program Output
The program's output can be of three types:

1. Address Found
~~~shell
Found: S
~~~
This output is printed if there is a single address "S" in the address database whose prefix matches the user-entered address "ADDRESS."

2. Address Requires Specification
~~~shell
Enable: CHARS
~~~
If multiple addresses matching the prefix "ADDRESS" are found in the address database, the program will print a line in the format above, providing a sorted list of enabled characters "CHARS." "CHARS" is a list of characters, sorted alphabetically, for which each character "C" has a corresponding address in the database whose prefix matches the concatenation of "ADDRESS" and "C".

3. Address Not Found
~~~shell
Not found
~~~
If no address in the address database has a prefix matching the user-entered address "ADDRESS," the program will print this message.

## Project limitations
It is prohibited to use the following functions:
- Memory allocation and deallocation functions from the malloc and free family (no dynamic memory usage is required).
- File I/O functions fopen, fclose, fscanf, feof, fseek, ftell (work with stdin, stdout, and stderr is sufficient).
- Search and sort functions qsort, lsearch, bsearch, hsearch (the goal is to focus on algorithmic and data structure considerations).

## Examples of Input and Output
Sample address file (adresy.txt):
~~~shell
Praha
Brno
Bruntal
Bratislava
~~~

Example: Searching for the word "brno"
~~~shell
$ ./keyfilter <adresy.txt
Enable: BP

$ ./keyfilter b <adresy.txt
Enable: R

$ ./keyfilter br <adresy.txt
Enable: ANU

$ ./keyfilter brn <adresy.txt
Found: BRNO

$ ./keyfilter be <adresy.txt
Not found

~~~
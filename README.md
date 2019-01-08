# CS50 Psets: Computer Science and General Programming

> record of programs implemented for CS50x from 2016 to 2018.

> Problem Sets (Psets): Pset 1 to Pset 5.

> Couldn't find the files for previous Pset solutions (the less comfortable versions from pset1 to pset3) I had implemented in C, so saving the solutions for the more comfortable versions implemented in Python for pset6 sentimentals part instead.


## Pset1: hello, mario, cash, credit
> Initially solved hello, mario(less comfortable version), cash(the less comfortable version) in C language in January, 2016.

> Solved hello, mario(more comfortable version), cash(the more comfortable version) in Python language in June, 2018.

- hello: a simple program printing "hello" on the screen.
  > first program in C, getting to know how to compile(using the make utility configured by CS50) and execute a .c file.
  
- mario: a program that prints out a full-pyramid of a specified height given by user.
    - the less comfortable version: print out a half-pyramid.
    
  > learned how to use conditions and loops
  > helped get familiar with using standard I/O (using CS50's training wheels: get_int()).
  
- cash: a program that calculates the minimum number of coins required to give a user change.
  > learned how to implement a greedy algorithm and how to handle the inherent imprecision of floating-point values.
  
- credit: a program that determines whether a provided credit card number is valid according to Luhn’s algorithm (If valid, print the which company it belongs to:American Express, MasterCard, or Visa).
  > learned how to use various math functions and operators to interact with numeral values.

## Pset2: caesar, vigenère, crack
> Initially, solved caesar(the less comfortable version), vigeniere(the less comfortable version) in C language in January, 2016.

> Solved crack(the more comfortable version) in Python in June, 2018.

- caesar: a program that encrypts messages using Caesar’s cipher.

- vigenère: a program that encrypts messages using Vigenère’s cipher.

- crack: a program that cracks passwords encryped by C's DES-based crypt function (hash function).
    
> learned about encryption and decryption, hash funcitons, ASCII values, how to use command-line arguments in programs, manipulate strings, and convert chars to integers.
      
## Pset3: fifteen
> Initially, Pset3 was to implement a game of fifteen in February, 2016. 

> Unfortunately, could not find source code I implemented.

## Pset4: whodunit, resize, recover
> Solved whodunit, resize(more comfortable version), recover in C language in February, 2016 and in July, 2018.

- whodunit: a program that reveals a hidden message in a BMP by removing the red noise in it.
  > learned how an image file is constructed by bits, specifically how a BMP file is formatted in hexadecimals to represent RGB in pixels.
  
  > Also learned how to use header files, structs, and got familiar with using file I/O.

- resize: a program that resizes (shrinks or enlarges) BMPs by a factor of f given by the user.
  > learned how to dynamically allocate memory using malloc and use valgrind to debug and check memory leaks.
  
- recover: a program that recovers JPEGs from a forensic image (.raw file).
  > learned how a JPEG file is formatted and about the FAT file system and blocks. 
  
## Pset5: speller
> Solved speller in C language in July, 2018.

- speller:  a program that spell-checks a file after loading a dictionary of words from disk into memory.

  > learned how to create a functions for a header file (c file -> h file), how to use pointers
  
  > Also learned how to implement data structures, specifically a trie for a dictionary of words.

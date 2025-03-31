# WordSearch

__Project 1 for CSE 31 - Assembly Language__

Recursive word search program written in C and exclusively in pointer notation.

The file wordsearch.c contains the program which can run in any linux enviorment with GCC. I would reccomend WSL in Visual Studio Code for the best experience.

Run the command `gcc wordsearch.c -g -o ws.o` to compile the program into "ws.o". For convenince I have provided my ws.o file but I would suggest running the command anyways.
Next run the command `./ws.o puzzle3.txt` where ws.o is the machine code and puzzle3.txt is the text file for the puzzle

This repository contains 4 puzzle text files. Each file follows the structure of the first line with the size of the grid (the length of one side) and the grid itself with each row seperated by line and each letter seperated by a space. 
You can use this structure to make your own puzzles to test out my program!

The word for puzzle1 is Hello, puzzle2 is Banana, puzzle3 is Deter, puzzle4 is Dining. My program is **not** case sensitive and will find all occurences of the word in the puzzle.

[Insert my logic of code here and pictures of my whiteboard logic]

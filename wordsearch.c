#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize); // first line of each puzzle .txt file will have the size of the puzzle block (e.g. 5 for a 5x5)
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    //printf("\nPrinting puzzle before search (in main):\n");
    printPuzzle(block);
    printf("\n");
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }

}

void printPuzzle2(int** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...

    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%-7d ", *(*(arr + i) + j));
        }
        printf("\n");
    }

}

char* convertWord(char* w){
    //printf("Inside CW\n");

    // until the end of the string
    for (int i = 0; i < strlen(w); i++){
        if ((*(w + i) >= 'a') && (*(w + i) <= 'z')){ // if lowercase, convert; else, pass
            *(w + i) = *(w + i) - 32; //32 being the difference in ascii values
        }
    }
    //printf("%s\n", w);

    return w;
}

int appendInt(int num1, int num2){ // num2 is the number to append to num1
    int temp = num2;\
    //int loops = 0;
    while(temp>0){
        num1 *= 10;
        temp /= 10;
    }
    num1 += num2;
    return num1;
}

bool lookAround(char** arr, int** path, int row, int col, char* word, int index){
    
    if (index == strlen(word)) {return true;} //base case
    bool found = false;
    
    // The default cases for the the bounds of the search
    // looks 1 step in every direction
    int i = row - 1;
    int j = col - 1;
    int endi = row + 1;
    int endj = col + 1;
    char letter = *(word + index);

    //printf("\n row: %d, col: %d\n ind: %d let: %c\n", row, col, index, letter);

    //normalizing x/i and y/j and accounting for potential errors
    if (row <= 0) i = 0; // if first row then don't look further up
    if (row >= bSize - 1) endi = bSize - 1; // if bottom row then don't look further down; doesn't update

    if(col == 0) j = 0;  // if first col then don't look further left 
    if (col >= bSize - 1) endj = bSize - 1;  // if last col then don't look further right; doesn't update
    
    //printf("\ni = %d, endi = %d \nj = %d, endj = %d\n", i, endi, j, endj);
    
    for(i; i <= endi; i++){
        //printf("loop row %d \n", i);
        
        (col == 0) ? (j = 0) : (j = col - 1);
        for(j; j <= endj; j++){ //checking every letter
            if(!found){
                //printf("%c(%d,%d) ", *(*(arr + i) + j), i, j); // print 1 step in every direction
                if((i == row && j == col)){
                    //printf("\nskipped over inputed letter %c\n", *(word + index - 1));
                    continue;
                }
                if((!(i == row && j == col)) && (*(*(arr + i) + j) == letter)){ // if current letter isn't previous letter and is the letter we're looking for
                    
                    //printf("found %c\n", letter);
                    found = lookAround(arr, path, i, j, word, index + 1); // if found then keep going ; ** recursion call **
                    if(found){
                        if(*(*(path + i) + j) == 0){
                            *(*(path + i) + j) = index + 1;
                        }else{
                            *(*(path + i) + j) = appendInt(*(*(path + i) + j), index + 1);
                        }
                    }
                } 
                if((i == endi ) && (j == endj )){  // if position is the last char in searching box
                    if((*(*(arr + i) + j) != letter) && !found){ // if it isn't letter
                        /*printf("\nreached the end and found nothing\n");
                        printf("i:%d endi:%d ", i, endi);
                        printf("j:%d endj:%d ", j, endj);
                        printf("curr:%c letter:%c ", *(*(arr + i) + j), letter);
                        printf("found:%d \n", found); */
                        //printf("i:%d j:%d \nendi%d endj:%d \ncurr:%c \n", i, j, endi, endj, (*(*(arr + i) + j)));
                        found = false;
                    }
                    
                }
            }
        }
        //printf(".\n");
    }


    return found;

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    //intializing path array for printing at the end
    int **pathArr = (int**)malloc(bSize * sizeof(int*));
    bool found = false;
    int count = 0;
    word = convertWord(word);

    for(int i = 0; i < bSize; i++){
        *(pathArr + i) = (int*)malloc(bSize * sizeof(int));
    }
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            *(*(pathArr + i) + j) = 0;
        }
    }

    //printf("Printing before search algo\n");

    // index for letter in word
    int index = 1;

    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){

            if( *(*(arr + i) + j) == *(word + index - 1)){ //if first letter found
                //printf("%c - (%d,%d)\n", *(*(arr + i) + j), i, j); //print first letter and its coordinate 
                found = lookAround(arr, pathArr, i, j, word, index);
                if(found){ //finding next letter
                    //*(*(pathArr + i) + j) = index;
                    //printf("\n\nsometing here\n\n");
                    count++;
                    *(*(pathArr + i) + j) = appendInt(index, *(*(pathArr + i) + j)); //if something else was found during lookAround it won't replace what was there and just appeneds to what is already there
                }
                
            } else{
                //printf("nope%c ", *(*(arr + i) + j));
            }
        }
        //printf("sP new line\n\n");
    }

    //printf("Printing after algo\n");

    //*(*(pathArr + 1) + 2) = 12;
    if(count){
        printf("Word found!\nPrinting the search path:\n");
        printPuzzle2(pathArr);
    } else{
        printf("Word not found!\n");
    }

    
    for(int i = 0; i < bSize; i++){
        free(*(pathArr + i));
    }
    free(pathArr);
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libraryStructures.h"
#include "library.h"
#include "user.h"
#include "librarian.h"
#include "utility.h"

////
// Code module for main library menu and file management
// Reads the book and initialises the problem data

// Initialise library data
// Input: 
// bookfile - name of book file
// theLibrary - library data structure

void initLibrary( char *bookFile, Library *theLibrary ) {

  theLibrary->maxBooks = 12;
  theLibrary->maxBorrowed = 4;

  // TO DO :
  
  // dynamically allocate the bookList array for storing books
  theLibrary->bookList = (Book*)malloc(sizeof(Book)*theLibrary->maxBooks);
  
  FILE* f = fopen(bookFile, "r");
  // check the book file exists 
  if(f == NULL) {
    // use the error message and exit the program if it does not
    printf("Error\nBook file does not exist: %s\n", bookFile);
    exit(0);
  }
  // open it if it exists
  // use the readBooks function to read in the file and add the book records into the bookList array
  theLibrary->numBooks = readBooks(f, theLibrary->bookList);
  // remember to close the file
  fclose(f);
  // Initialise the User data
  theLibrary->theUser.numBorrowed = 0;
  for(int i = 0; i < 4; i ++) {
    theLibrary->theUser.borrowed[i] = NULL;
  }

  return;
}

// Read in book file and create the books data structure
// the book file is in a fixed format:
// * book author
// * book title
// * blank line
// Input:
//   books - file pointer to text input file
//   bookList - alocated array for storing Book structures
// Output:
//   numBooks - number of books read

int readBooks( FILE *books, Book *bookList ) {

  int numBooks = 0;

  char buf[1024];

  // TO DO:
  
  // read from the book file pointer
  // assign values to a Book structure in the bookList array for each complete record
  // read data until the file ends
	int i = 0;
	while (fgets(buf, sizeof(buf), books) != NULL) {
    if(i%3==0) {
      numBooks ++;

			strcpy(bookList[numBooks-1].author, buf);
			int l = strlen(bookList[numBooks-1].author);
			for(int j = l-1; j >= 0; j --) {
				if(bookList[numBooks-1].author[j] == '\n') bookList[numBooks-1].author[j] = '\0';
			}
		}
		if(i%3==1) {
			strcpy(bookList[numBooks-1].title, buf);
			int l = strlen(bookList[numBooks-1].title);
			for(int j = l-1; j >= 0; j --) {
				if(bookList[numBooks-1].title[j] == '\n') bookList[numBooks-1].title[j] = '\0';
			}
		}
		if(i%3==2) {
      bookList[numBooks-1].available = 1;
		}
    i++;
  }
  
  return numBooks;
}

// Free any allocated library data
// Input: 
// theLibrary - library data structure

void exitLibrary( Library *theLibrary ) {

  // TO DO:

  // free the allocated lists
  for(int i = 0; i < theLibrary->maxBorrowed; i ++) {
    theLibrary->theUser.borrowed[i] = NULL;
  }
  free(theLibrary->bookList);
  

  return;
}

// DO NOT ALTER THIS FUNCTION
// Library menu system

void libraryCLI( char *bookFile ) {
    int libraryOpen = 1;
    int option;

    // create the library structure
    Library *theLibrary = (Library *)malloc( sizeof(Library) );

    initLibrary( bookFile, theLibrary );
   
    while( libraryOpen ){
        printf("\n Main menu options\n 1 User login\n 2 Librarian login\n 3 Exit system\n Choice:");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nUser login\n");
            userCLI( theLibrary );
        }
        else if( option == 2 ) {
            printf("\nLibrarian login\n");
            librarianCLI( theLibrary );
        }
        else if( option == 3 ) {
            libraryOpen = 0;
            printf("\nClosing\n");
        }
        else
            printf("\nUnknown option\n");
    }

    exitLibrary( theLibrary );

    // free the library structure
    free( theLibrary );

    return;
}


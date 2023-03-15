#include <stdio.h>
#include <stdlib.h>

#include "libraryStructures.h"
#include "user.h"
#include "utility.h"

////
// Code module for the library user
// They can look for available books,
// borrow and return books

// List the books that are available to borrow
// Input
// bookList - the array of Book structures
// numBooks - the number of books

void listAvailableBooks( Book *bookList, int numBooks ) {

  // TO DO :  

  // print out available books with format "list number - author - title" on each line
  for(int i = 0; i < numBooks; i ++) {
      if(bookList[i].available == 0) continue;
      printf("%d - %s - %s\n", i, bookList[i].author, bookList[i].title);
  }
  return;
}

// Borrow a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void borrowBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  

  // For any error message you should return to the menu

  // check that the user can borrow a book
  if(theUser->numBorrowed >= maxBorrowed) {
    printf("You have to return a book before you can borrow another\n");
    return;
  }

  // request the choice of book
  int choice = 0;
  printf("Which book? (number):");
  scanf("%d", &choice);
  getchar();

  // check that the choice is valid 
  // error messages
  if(choice >= numBooks) {
    printf("Error\nInvalid choice\n");
    return;
  }
  if(bookList[choice].available == 0) {
    printf("Book is not available\n");
    return;
  }
  
  
  // borrow the book, update the data structures
  bookList[choice].available = 0;
  theUser->borrowed[theUser->numBorrowed] = &bookList[choice];
  theUser->numBorrowed ++;

  return; 
}

// List books I have borrowed 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// maxBorrowed - max books we can borrow

void listMyBooks( User *theUser, Book *bookList, int maxBorrowed ) {

  // TO DO :  

  // list my books in format "number - author - title"
  for(int i = 0; i < maxBorrowed; i ++){
    if(theUser->borrowed[i] == NULL) break;
    printf("%d - %s - %s\n", i, theUser->borrowed[i]->author, theUser->borrowed[i]->title);
  }

  return;
}

// Return a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void returnBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  

  // For any error message you should return to the menu

  // check that we have borrowed books 
  // error messages
  if(theUser->numBorrowed == 0) {
    printf("Error\nYou have not borrowed any books\n");
    return;
  }

  // request the choice of book 
  // message
  int choice = 0;
  printf("Which book? (number):");
  scanf("%d", &choice);
  getchar();

  // check the choice is valid
  // error messages
  if(choice >= theUser->numBorrowed) {
    printf("Error\nInvalid choice\n");
    return;
  }

  // return the book and update data structures 
  theUser->borrowed[choice]->available = 1;
  theUser->borrowed[choice] = NULL;
  theUser->numBorrowed --;

  return;
}

// DO NOT ALTER THIS FUNCTION

// Menu system for library user

void userCLI( Library *theLibrary ) {
    int userLoggedIn = 1;
    int option;

    while( userLoggedIn ){
        printf("\n User options\n 1 List available books\n 2 Borrow book\n 3 Return book\n 4 Log out\n Choice:");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nList available books:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
        }
        else if( option == 2 ) {
            printf("\nBorrow book from library:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
            borrowBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 3 ) {
            printf("\nReturn book from my list:\n");
            listMyBooks( &(theLibrary->theUser), theLibrary->bookList, theLibrary->maxBorrowed );
            returnBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 4 ) {
            userLoggedIn = 0;
            printf("\nLogging out\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}


/*
author: Richard

This program implements the game of
hangman.  Start with 5-letter words.
This could be modified to commandline input.
Version 1.0

1. read dictionary, make a list of words
2. make a list of 5-letter words
3. loop until done
3a   get letter from the user
3b   test if the letter is in the word
3c   print the state of the game

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LEN 5
char hangman_str[] = "_ _ _ _ _"; //note the spaces
char *theword;

// function declarations
char *read_dict(char *filename) ;
char *choose_word() ;
char get_user_input() ;

void print_word() ;


/**********************
main
 *********************/
int main() {

  print_word();

  return 0;
}

/**********************
read_dict
 *********************/
char *read_dict(char *filename) {
  char *dict;
  // open file

  //allocate memory

  // read each line
  // copy it to dict if it has the right length

  return dict;
}

// choose a random word of the right length
char *choose_word() {
  char *word;

  return word;
}

/**********************
get_user_input
 *********************/
char get_user_input() {
  char in;

  return in;
}


/**********************
test_letter
updates hangman_str
 *********************/
int test_letter() {


}

void draw_pict() {

}

void print_word() {

  printf("%s \n", hangman_str);
}

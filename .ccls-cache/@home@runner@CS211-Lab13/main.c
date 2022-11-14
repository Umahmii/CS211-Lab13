#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//I COULD NOT FOR THE LIFE OF ME INCLUDE MATH.H
//enjoy mathless search haha

//MufinCo 2022

#define NROWS 11
#define NCOLS 11
#define START_R (NROWS/2)
#define START_C (NCOLS/2)


#define NORTH 'n'
#define SOUTH 's'
#define EAST  'e'
#define WEST  'w'
#define QUIT  'q'
#define BLANK 'b'
#define ERROR 'r'

/**
 * starter code for the 'search' program/game.
 *
 * The given code takes care of two of the tasks in the program:
 *
 *      - reading and interpreting a user command via the read_cmd
 *          function.  Read the banner comment and examine the example
 *          usage of the function in main for details.
 *
 *      - handling optional command line arguments which allow a 
 *          the user (tester) to specify explicitly the location of
 *          the pot-o-gold instead of that location being randomized
 *          as in the default mode.
 *
 */

/**
 * func:  read_cmd
 * desc:  (attempts to) read a single line from standard input, and 
 *          returns one of the following:
 *
 *          NORTH : if the first non-whitespace character is either
 *                  'n' or 'N'
 *          SOUTH : if the first non-whitespace character is either
 *                  's' or 'S'
 *          EAST  : if the first non-whitespace character is either
 *                  'e' or 'E'
 *          WEST  : if the first non-whitespace character is either
 *                  'w' or 'W'
 *          QUIT  : if the first non-whitespace character is either
 *                  'q' or 'Q' OR an input line cannot be read (this
 *                  happens if EOF is read terminating the input; from 
 *                  the terminal, this happens if the user types ctrl-D 
 *                  (in UNIX at least))
 *          BLANK : if the user entered a blank/empty line
 *          ERROR : if the user entered an invalid command
 *
 */

char read_cmd() {

    char buf[128];

    // this happens when fgets reads 'EOF'.  This happens
    //   when the user types CTRL-D
    if(fgets(buf, 128, stdin) == NULL)
        return 'q';

    int n = strlen(buf);

    int i=0;

    while(i<n && isspace(buf[i]))
        i++;

    if(i==n)
        return BLANK;  // entire line is whitespace (incl newline)
    char c = buf[i];

    switch(c) {
        case 'n':
        case 'N': return NORTH;
        case 's':
        case 'S': return SOUTH;
        case 'e':
        case 'E': return EAST;
        case 'w':
        case 'W': return WEST;
        case 'q':
        case 'Q': return QUIT;
        default: 
                  return ERROR;

    }
}

/**
 * func: inrange
 * desc: simple predicate function determining whether a 
 *          given coordinate (r,c) is within the boundaries
 *          of the "board" (if yes, returns true; if no,
 *          returns false).
 */
int inrange(int r, int c) {
    if(r < 0 || c < 0 || r >= NROWS || c >= NCOLS) 
        return 0;
    else
        return 1;
}


// float two_dis(float p_row, float p_col, float g_row, float g_col) {
//    float dis = sqrt(pow(g_row - p_row, 2) + pow(g_col - p_col, 2) * 1.0);
//    return dis;
// }

void warmOrCold(int pn_row, int pn_col, int p_row, int p_col, int g_row,int g_col){ 
  if (abs(pn_row-g_row) > abs(p_row-g_row) || abs(pn_col-g_col) > abs(p_col-g_col)){
    printf("GETTING COLDER!\n");
  }
  else if ((abs(pn_row-g_row) < abs(p_row-g_row) || abs(pn_col-g_col) < abs(p_col-g_col))){
    printf ("GETTING WARMER!\n");
  }
  else {
    printf("unckown");
  }
}

void ow(){
  printf ("OUCH!\n");
}

int main(int argc, char *argv[]) {
    int g_row, g_col, p_row, p_col, pn_row, pn_col;
    p_row= START_R;
    p_col= START_C;
    pn_row = START_R;
    pn_col = START_C;


    int randomize = 1;
    // float oldDistance;
    // float currentDistance;
    int counter = 0;
    int skip = 0;
    srand(1); //random seed set to 1

    for(int i=0; i<argc; i++) {
        printf(" argv[%i] : '%s'\n", i, argv[i]);
    }
    if(argc == 3){
        int r1 = sscanf(argv[1], "%i", &g_row);  // row coord of gold
        int r2 = sscanf(argv[2], "%i", &g_col);  // row coord of gold
        if(r1==0 || r2==0 || !inrange(g_row, g_col) ||
                (g_row == START_R && g_col == START_C))
            printf("bad cmd-line args: using random location for gold\n");
        else
            randomize = 0;
    }
    else if(argc != 1) 
            printf("bad cmd-line args: using random location for gold\n");

    if(randomize) {
      g_row = rand()%NROWS;
      g_col = rand()%NCOLS;
      while (g_row == 5 && g_col == 5){
        g_row = rand()%NROWS;
        g_col = rand()%NCOLS;
      }
    }

    fprintf(stderr, "pot-o-gold location: (%d, %d)\n", g_row, g_col);
    //oldDistance = sqrt(pow(g_row - p_row, 2) + pow(g_col - p_col, 2) * 1.0);
    int done = 0;

    // demo loop...
    while(!done) {
        printf("Direction: ");
        char c = read_cmd();

        if (c=='n'){
          if (inrange(p_row+1, p_col) == 0){
            ow();
            skip = 1;
          }
          else{
            pn_row = p_row+1;
          }
        }

        else if (c=='e'){
          if (inrange(p_row, p_col+1) == 0){
            ow();
            skip = 1;
          }
          else{
            pn_col = p_col+1 ;
          }
        }

        else if (c=='s'){
          if (inrange(p_row-1, p_col) == 0){
            ow();
            skip = 1;
          }
          else{
            pn_row = p_row-1;
          }
        }

        else if (c=='w'){
          if (inrange(p_row, p_col-1) == 0){
            ow();
            skip = 1;
          }
          else{
            pn_col = p_col-1;
          }
        }

        else if (c=='b' || c=='r'){
          printf("Invalid input. Try again.\n");
          skip = 1;
        }

        else if(c=='q') 
            done = 1;
        
        if (skip == 0){
          warmOrCold(pn_row, pn_col, p_row, p_col, g_row, g_col);
          p_row = pn_row;
          p_col = pn_col;
          counter++;
        }
        skip = 0;
        //fprintf(stderr, "DEMO:  read_cmd() returned '%c'\n Player Position: %i, %i \n", c, p_row, p_col);
        if (p_row == g_row && p_col == g_col){
          printf ("HORRAY!\n\nTotal Moves: %i", counter);
          done = 1;
        }
    }

}
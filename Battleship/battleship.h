#include <stdbool.h>

//the number of rows in our battleship game
#define NUM_ROWS 8
//the number of columns in our battleship game
#define NUM_COLUMNS 8
//the maximum number of moves we allow, if a game is not won by this many moves
//the player loses
#define MAX_MOVES 30

//battleship_grid contains the information we need to track during
//our game of Battleship.
struct battleship_grid
{
    //battle_field tracks the locations on Player A's 
    //grid that are occupied by ships. 
    //A 1 at (row,column) indicates that part of a ship is in 
    //(row,column),  a 0 indicates it is not. 
    int  battle_field[NUM_ROWS][NUM_COLUMNS];

    //battle_field_guessed contains bool values indicating if 
    //Player B has fired at specific locations. 
    //A true at (row,column) indicates player B has fired at
    //(row,column) previously.
    bool battle_field_guessed[NUM_ROWS][NUM_COLUMNS];

    //num_moves is the number of moves taken on the 
    //battleship_grid so far.
    int  num_moves;
};

struct battleship_grid* make_empty_battleship_grid();
bool in_bounds(int x, int y);
bool not_fired_at(struct battleship_grid* g, int x, int y);
bool fire(struct battleship_grid* g, int x, int y);
bool win(struct battleship_grid* g);
bool gameover(struct battleship_grid* g);
bool can_add_ship(struct battleship_grid* g, int x0, int y0, int width, int height);
void add_ship(struct battleship_grid* g, int x0, int y0, int width, int height);
void peek(struct battleship_grid* g);
void print_battle_field(struct battleship_grid* g);
void free_battleship_grid(struct battleship_grid* g);
struct battleship_grid* read_battleship_grid();
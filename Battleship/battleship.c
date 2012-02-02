#include <stdlib.h>
#include <stdio.h>
#include "battleship.h"

//Create a new empty battleship_grid for a new game of Battleship.
//Precondition:  True.
//Postcondition: Returns a new battleship_grid to be used in starting up a new game of battleship.
//In the returned battleship_grid, no moves have been made, no ships are on player A's grid,
//and player B has not fired at any square yet.
struct battleship_grid* make_empty_battleship_grid()
{
	struct battleship_grid* g = malloc(sizeof(struct battleship_grid));
	
	g->num_moves = 0;
	
	for (int i=0; i<NUM_ROWS; i++) {
		for (int j=0; j<NUM_COLUMNS; j++) {
			g->battle_field[i][j] = 0;
			g->battle_field_guessed[i][j] = false;
		}
	}
	
	return g;
}

//Determines if a given (row,column) coordinate is a valid battleship_grid location. 
//Parameters:    int row - the row coordinate of the location
//               int column - the column coordinate of the location
//Precondition:  True.
//Postcondition: Returns true if (row,column) is within the bounds of the battleship_grid ((0,0) to
//(NUM_ROWS,NUM-1_COLUMNS-1), inclusive) and false otherwise.
bool in_bounds(int row, int column)
{
	if (row >= 0 && row <= NUM_ROWS-1 && column >= 0 && column <= NUM_COLUMNS-1) {
		return true;
	} else {
		return false;
	}
}

//Determines if a given (row,column) coordinate has been fired at previously.
//Parameters:    battleship_grid* g - the battleship grid
//               int row - the row coordinate of the location
//               int column - the column coordinate of the location
//Precondition:  in_bounds(row,column) == true
//Postcondition: Returns true if (row,column) has been fired at previously, and
//false otherwise.
bool fired_at(struct battleship_grid* g, int row, int column)
{
	if (g->battle_field_guessed[row][column] == 1) {
		return true;
	} else {
		return false;
	}
}

//Player B fires at (row,column).
//Parameters:    battleship_grid *g - the battleship grid
//               int row - the row coordinate of the location
//               int column - the column coordinate of the location
//Precondition:  in_bounds(row,column) == true && fired_at(g,row,column) == false
//Postcondition: Increments num_moves for g by one and flags the square (row,column) as fired at for g. Returns
//true if (row,column) contained part of a ship in g, and false otherwise.
bool fire(struct battleship_grid* g, int row, int column)
{
	g->battle_field_guessed[row][column] = 1;
	g->num_moves++;
	
	if (g->battle_field[row][column] == 1) {
		return true;
	} else {
		return false;
	}
}

//Determines if the game of battleship represented by g has been won by Player B.
//Parameters:    battleship_grid *g - the battleship grid
//Precondition:  g->num_moves <= MAX_MOVES
//Postcondition: Returns true iff every grid square in g containing a ship has been fired at.
bool win(struct battleship_grid* g)
{
	for (int i=0; i<NUM_ROWS; i++) {
		for (int j=0; j<NUM_COLUMNS; j++) {
			if (g->battle_field[i][j] == 1 && g->battle_field_guessed[i][j] == 0) {
				return false;
			}		
		}
	}
	
	return true;
}

//Determines if the game of battleship represented by g is over.
//Parameters:    battleship_grid *g - the battleship grid
//Precondition:  True
//Postcondition: Returns true if every grid square in g containing a ship has been fired at or
//g >= MAX_MOVES, and false otherwise.
bool gameover(struct battleship_grid* g)
{
	if (win(g) == true || g->num_moves >= MAX_MOVES) {
		return true;
	} else { 
		return false;
	}
}

//Determines if a ship, represented by the supplied parameters, can be added to g. This function
//is to be used to determine if player A has selected a valid location to place one of their ships.
//Parameters:    battleship_grid *g - the battleship grid
//               int row0 - the starting row of the ship
//               int column0 - the starting column of the ship
//               int row_width - the number of rows the ship takes up
//               int column_width - the number of columns the ship takes up
//Precondition:  True
//Postcondition: Returns true if every square the ship would occupy is currently unoccupied
//and is within the bounds of the battleship_grid (as per in_bounds function), 
//otherwise false is returned. g remains unchanged.
bool can_add_ship(struct battleship_grid* g, int row0, int column0, int row_width, int column_width)
{
	if (g->battle_field[row0][column0] == 1 || in_bounds(row0,column0) == false) {
		return false;
	}
	
	// Note: Either row_width or column_width will be 0 after this
	row_width--;
	column_width--;
	
	while (row_width != 0) {
		row0++;
		if (g->battle_field[row0][column0] == 1 || in_bounds(row0,column0) == false) {
			return false;
		}
		row_width--;
	} while (column_width != 0) {
		column0++;
		if (g->battle_field[row0][column0] == 1 || in_bounds(row0,column0) == false) {
			return false;
		}
		column_width--;
	} 
	
	return true;
}

//Adds a ship, represented by the supplied parameters, to g. This function
//is called to place one of player A's ships.
//Parameters:    battleship_grid *g - the battleship grid
//               int row0 - the starting row of the ship
//               int column0 - the starting column of the ship
//               int row_width - the number of rows the ship takes up
//               int column_width - the number of columns the ship takes up
//Precondition:  can_add_ship(g,row0,column0,row_width,column_width) == true
//Postcondition: Adds the ship specified by the parameters to g. All the squares the ship
//is in are properly flagged as occupied in g. Num_moves does not change. Likewise, which
//grid squares have been shot at in g does not change.
void add_ship(struct battleship_grid* g, int row0, int column0, int row_width, int column_width)
{
	
	g->battle_field[row0][column0] = 1;
	
	// Note: Either row_width or column_width will be 0 after this
	row_width--;
	column_width--;
	
	while (row_width != 0) {
		row0++;
		g->battle_field[row0][column0] = 1;
		row_width--;
	} while (column_width != 0) {
		column0++;
		g->battle_field[row0][column0] = 1;
		column_width--;
	} 
	
	return;
}

//Prints Player A's grid in g to standard output.
//Parameters: battleship_grid* g - the battleship_grid
//Precondition: True.
//Postcondition: Player A's grid, contained in g, is printed to standard output.
//The uppper left corner is printed as (0,0),
//the bottom right corner is (NUM_ROWS-1, NUM_COLUMNS-1). The value displayed at location
//(row,column) is 'O' if it contains a ship and 'E' if it doesn't. 
void peek(struct battleship_grid* g)
{
	for(int i = 0; i < NUM_ROWS; i++)
	{
		for(int j = 0; j < NUM_COLUMNS; j++)
		{
			if(g->battle_field[i][j] == 0)
				printf("E");
			else
				printf("O");
		}
		printf("\n");
	}
}

//Prints Player B's grid in g to standard output.
//This function is used by main during the course of a battleship game to update Player B
//(the user) of their current grid status.
//Parameters: battleship_grid* g - the battleship_grid to print out
//Precondition: True.
//Postcondition: g is printed to standard output. The uppper left corner is (0,0),
//The bottom right corner is (NUM_ROWS-1, NUM_COLUMNS-1). The value displayed at location
//(x,y) is * if (x,y) has not been shot at, otherwise it is 'H' if it contains a ship and 
//'M' if it doesn't.
void print_battle_field(struct battleship_grid* g)
{
	for(int i = 0; i < NUM_ROWS; i++)
	{
		for(int j = 0; j < NUM_COLUMNS; j++)
		{
			if(g->battle_field_guessed[i][j] == false)
				printf("*");
			else if(g->battle_field[i][j] == 0)
				printf("M");
			else
				printf("H");
		}
		printf("\n");
	}
}


//Read a battleship_grid from standard input. The only standard input expected by this function
//is a player A grid indentical to the format produced by peek.
//Precondition: True.
//Postcondition: Returns a new battleship_grid structure. In the new struct, the player A grid reflects that read in.
//The expected form of the player A grid read in is a NUM_ROWS by NUM_COLUMNS grid. The uppper left corner read in corresponds to (0,0) 
//, the bottom right corner corresponds to (NUM_ROWS-1, NUM_COLUMNS-1). The value at location
//(row,column) is 'O' if it contains a ship and 'E' if it doesn't (as per peek). num_moves is set to 0 in the new battleship_grid
//and player B's grid has no shots fired. Note that *any* number of player A grid squares may be 'O' instead of 'E' (from 0 to the entire
//grid.
struct battleship_grid* read_battleship_grid()
{
	struct battleship_grid* g = make_empty_battleship_grid();
	char input_ch;
	
	for(int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLUMNS; j++) {
			input_ch = getchar();
			if (input_ch == 'O'){
				g->battle_field[i][j] = 1;
			}
		}
		getchar();
	}
	
	return g;
}

//Frees the memory for the battleship_grid g points to.
//Precondition:  The battleship_grid g points to was created with malloc.
//Postcondition: The memory g points to is freed.
void free_battleship_grid(struct battleship_grid* g)
{
	free(g);
}





//A main function to play the game of battleship.
int main(void)
{

	//create an empty battleship grid
	struct battleship_grid* g = make_empty_battleship_grid();

	//populate it with ships of the correct sizes and number
	int a[] = {5, 4, 3, 3, 2};
	int index = 0;
	
	srand(15);

	while(index < 5)
	{
		int x0     = rand() % 8;
		int y0     = rand() % 8;
		int dir    = rand() % 2;
		int width;
		int height;
		if(dir == 0)
		{
			width = a[index];
			height = 1;
		}else
		{
			width = 1;
			height = a[index];
		}

		if(can_add_ship(g,x0,y0,width,height))
		{
			add_ship(g,x0,y0,width,height);
			index++;
		}else
		{

		}
	}

	//play the battleship game
	do{
		print_battle_field(g);
		printf("\nEnter a row number followed by a column number: ");
		int x;
		int y;
		scanf("%d %d", &x, &y);
		if(x == -1 && y == -1)
		{
			peek(g);
		}else if(in_bounds(x,y) && !fired_at(g,x,y))
		{
			if(fire(g,x,y))
				printf("Hit!!!\n");
			else
				printf("Miss!!!\n");
		}else
		{
			printf("Invalid square. Try Again.\n");
		}			
	}while(!gameover(g));

	if(win(g))
		printf("You Win!!!\n");
	else
	{
		printf("You Lose!!!\n");
	}

	free_battleship_grid(g);
	g = NULL;

	return 0;
}



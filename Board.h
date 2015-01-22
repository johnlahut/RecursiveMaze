/*
Author: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Board.h
Purpose: Provides the specification for Board. A board is a dynamically allocated 2D array of Cells.
			A board represents a maze.
*/


#include "Cell.h"			//For use of a Cell structure
#include "Location.h"		//For used of a Location structure
#include <iostream>			//For cout

const int INIT_HEIGHT = 2;
const int INIT_LENGTH = 2;

using namespace std;

/*

A gameboard has a border of inactive spaces, however the client accesses it as normal. 
To compensate observor accessor methods subtract one where necessary
Ex for a default board

[*][*][*][*]
[*][ ][ ][*]
[*][ ][ ][*]
[*][*][*][*]

*/


/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Board();
	Creates a new Board object. Default size is a 2x2 board 

Board(int length, int width);
	Creates a new Board object with a specified height and width

Board(const Board &orig);
	Creates a new Board object that is identical to orig

~Board();
	Deallocates a the Board from memory

void SetWall(Location loc, bool wall);
	Sets the given location's wall value (true or false)

void SetVisited(Location loc, bool visited);
	Sets the given location's visited value (true or false)

bool IsVisited(Location loc);
	Returns true to the caller if the given location is visited, false otherwise

bool IsWall(Location loc);
	Returns true to the caller if the given location has a wall, false otherwise

int GetHeight();
	Returns the current height of the board

int GetLength();
	Returns the current length of the board

void Print();
	Prints the current board

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Private Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Setup();
	Initalizes all values of each cell to false. 
*/

class Board
{

	public:

		//pre: none
		//post: A default 2x2 board has been created
		Board();

		/***************************************************************************************************/

		//pre: none
		//post:	A board with a given length and width has been created
		Board(	/*in*/int length,	//length of the new board
				/*in*/int width);	//width of the new board

		/***************************************************************************************************/
		
		//pre: orig is a valid board class
		//post: A deep copy of orig has been created
		Board(/*in*/const Board &orig);	//board to copy

		/***************************************************************************************************/

		//pre: Board has been initialized
		//post: Board has been deallocated from memory
		~Board();
		
		/***************************************************************************************************/

		//pre: Board has been initalized, loc is a valid Location within the bounds of the board
		//post:	The given Location's open value has been set appropriately 
		void SetOpen(/*in*/Location loc,	//valid location within the bounds of the board
					/*in*/bool open);		//desired boolean value for the given location

		/***************************************************************************************************/

		//pre: Board has been initialzed, loc is a valid Location within the bounds of the board
		//post: True is returned to the caller if the given Location is visited, false otherwise
		/*out*/bool IsOpen(					//boolean value returned to the caller
							/*in*/Location loc);//valid location within the bounds of the board

		/***************************************************************************************************/

		//pre: Board has been initialized
		//post: returns the height of the board
		/*out*/int GetHeight();					//height is returned to the caller

		/***************************************************************************************************/

		//pre: Board has been initialized
		//post: returns the length of the board
		/*out*/int GetLength();					//length is returned to the caller

		/***************************************************************************************************/

		//pre: Board has been initalized
		//post: prints the current board to the console
		void Print();

		/***************************************************************************************************/

	private:

		//pre: Board has been initialized
		//post: each cell in the board has had its wall and visited value set to false
		void Setup();

		/***************************************************************************************************/

		

		//PDM's

		Cell **gb;			//to represent a 2D array of cell pointers
		int height;			//height of the board
		int length;			//length of the board
};
/*
Author: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Board.cpp
Purpose: Provides the implementation of a board.
*/
#include "Board.h"
#include <iostream>

/*

A gameboard has a border of inactive spaces, however the client accesses it as normal.
To compensate observor accessor methods subtract one where necessary
Ex for a default board

[*][*][*][*]
[*][ ][ ][*]
[*][ ][ ][*]
[*][*][*][*]

*/

//pre: none
//post: A default 2x2 board has been created
Board::Board()
{
	height = INIT_HEIGHT+2;
	length = INIT_LENGTH+2;

	gb = new Cell*[height];
	for (int i = 0; i < height; i++)
	{
		gb[i] = new Cell[length];
	}

	Setup();
}


/***************************************************************************************************/


//pre: none
//post:	A board with a given length and width has been created
Board::Board(	/*in*/int inLength,	//length of the new board
				/*in*/int inHeight)	//width of the new board
{
	length = inLength+2;
	height = inHeight+2;

	gb = new Cell*[height/*row*/];
	for (int i = 0; i < height; i++)
	{
		gb[i] = new Cell[length/*col*/];
	}

	Setup();
}


/***************************************************************************************************/


//pre: orig is a valid board class
//post: A deep copy of orig has been created
Board::Board(/*in*/const Board &orig)	//board to copy
{
	length = orig.length;
	height = orig.height;
	Location loc;

	gb = new Cell*[height];
	for (int i = 0; i < height; i++)
	{
		gb[i] = new Cell[length];
	}

	Setup();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			loc.row = i; loc.col = j;

			if (!orig.gb[i][j].open)
				gb[i][j].open = false;
		}
	}

}


/***************************************************************************************************/


//pre: Board has been initialized
//post: Board has been deallocated from memory
Board::~Board()
{
	for (int i = 0; i < height; i++)
		delete[] gb[i];

	delete[] gb;
}


/***************************************************************************************************/


//pre: Board has been initalized, loc is a valid Location within the bounds of the board
//post:	The given Location's open value has been set appropriately 
void Board::SetOpen(	/*in*/Location loc,	//valid location within the bounds of the board
						/*in*/bool open)//desired boolean value for the given location
{
	gb[loc.row+1][loc.col+1].open = open;
}


/***************************************************************************************************/



//pre: Board has been initialzed, loc is a valid Location within the bounds of the board
//post: True is returned to the caller if the given Location is visited, false otherwise
/*out*/bool Board::IsOpen(					//boolean value returned to the caller
							/*in*/Location loc)//valid location within the bounds of the board
{
	return(gb[loc.row+1][loc.col+1].open);
}


/***************************************************************************************************/


//pre: Board has been initialized
//post: returns the height of the board
/*out*/int Board::GetHeight()					//height is returned to the caller
{
	return height-2;
}


/***************************************************************************************************/



//pre: Board has been initialized
//post: returns the length of the board
/*out*/int Board::GetLength()					//length is returned to the caller
{
	return length-2;
}


/***************************************************************************************************/


//pre: Board has been initalized
//post: prints the current board to the console
void Board::Print()
{
	for (int i = 1; i < height-1; i++)
	{
		for (int j = 1; j < length-1; j++)
		{
			if (gb[i][j].open)
				cout << " O ";
			else
				cout << " | ";
		}
		cout << endl << endl;
	}

	cout << endl;
}


/***************************************************************************************************/



//pre: Board has been initialized
//post: each cell in the board has had its wall and visited value set to false
void Board::Setup()
{
	Location loc;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			loc.row = i; loc.col = j;
			if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
			{
				gb[i][j].open = false;
			}
			else
			{
				gb[i][j].open = true;
			}
		}
	}

}
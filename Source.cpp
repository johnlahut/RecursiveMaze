/*
Author: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Source.cpp
Assumptions: Maze entry point will always be top left coordinate, and exit point will always be
			 bottom right coordinate. Input file is properly formatted.
PURPOSE: Given:
			A gameboard
			A starting location
			A stack data structure to track each path
			A starting number of maze paths
			and an output stream to write the solution to,
		this program finds all possible paths through a maze using recursion. The function continues to find
		all possible paths by visiting every location. 

		Its base case is that it has no more available spaces to
		check, essentially when the function reaches its starting location. 

		Each call the function attempts to
		move either south, east, north, west, respecively. If it is successful in its attempt (function value
		returns true), the function will invoke a recursive call. It will continue to do so until a movement
		is not possible in that direction (function will return false). It will try every possible movement 
		at a given location. If the function cannot move further at a given location, it will backtrack one
		space and attempt to move in a different direction. 

		Once the function backtracks all the way back to 
		its original location, it will return false, reaching a base case. 

		If the function reaches the exit point,
		it will write its current path to the given output file, and move backwards a space. 
		
INPUT:	Program reads in a file from the console and validates it. Must contain only letters and three letters after the period.
		First line of file is the size of the board, all following coordinates
		are within the bounds of the size of the board, and represent walls
OUTPUT: Program writes all solutions to "solution.out". If there was at least one solution, the program
		writes all possible paths (1-n) and lists directions needed to travel to reach the exit
Error checking: Program checks for a valid file, checks to make sure size of board is greater than zero
				(row>0, col>0)
*/

#include "Stack.h"				//For use of stack
#include "Exceptions.h"			//Exceptions
#include "Location.h"			//Location struct
#include "Board.h"				//For use of a board
#include <iostream>				//cout
#include <fstream>				//File vars
#include <string>				//Writing strings to file

using namespace std;

//At a given location, possible movements are up(NORTH), down(SOUTH), right(EAST), left(WEST)
enum Direction {NORTH, SOUTH, EAST, WEST};

//int constants
const int UPPER_ASCII_LIMIT = 90;									//ascii value of Z
const int LOWER_ASCII_LIMIT = 65;									//ascii value of A

//String constants 
const string FILE_OUT = "solution.out";								//Output file to write solutions to
const string NORTH_STR = "NORTH";									//North string literal
const string SOUTH_STR = "SOUTH";									//South string literal
const string EAST_STR = "EAST";										//East  string literal
const string WEST_STR = "WEST";										//West string literal
const string START = "START. ENTER FROM NORTH.";					//Entry string literal
const string PATH_NUM = "PATH NUMBER: ";							//Path number string literal
const string END = "EXIT SOUTH. END PATH.";							//Path exit string literal	
const string NO_SOLUTIONS = "No solutions";							//No solutions literal
	
const string ENTER_FILE = "Enter name of maze file...";				//User prompt
const string SUCCESS_STR = "Success! Generating paths and writing solution to 'solution.out'";
const string EXIT_BLOCKED = "Exit is blocked. No solutions.";		//Exit blocked error
const string ENTRY_BLOCKED = "Entry point blocked. No solutions.";	//Entry point blocked error
const string FILE_READ_ERR = "Error reading file.";					//File read error
const string FILE_FORMAT_ERR = "Bad file format.";					//Entry format error


/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Location ModifyLocation(Location loc, Direction direction);
	Given: a location, and a direction
		-> modifies that location appropriately
			If moving north, row is decremented
			If moving south, row is incremented
			If moving east, col is incremented
			If moving west, col is decremented

void WriteSolutionToFile(ofstream &outdat, StackClass solution, int &solutionNum);
	Given: a output file stream, a StackClass, and a solution number
		-> writes the current solution stack to the file stream

Board CreateBoardFromFile(string fileIn, bool &error);
	Given: a properly formatted file, boolean value 
		-> returns a new Board to the caller with proper dimensions and walls
			returns a boolean value representing a good file read or not
*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Method Prototypes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Location ModifyLocation(Location loc, Direction direction);
void WriteSolutionToFile(ofstream &outdat, StackClass solution, int solutionNum);
Board CreateBoardFromFile(string fileIn, bool &error);
bool FindPaths(Board &gb, Location loc, StackClass &path, int &counter, ofstream &outdat, ItemType curentItem);



/***************************************************************************************************/
/***************************************************************************************************/


void main()
{
	int counter = 0;										//Current number of solutions
	int ascii = 0;											//var to hold ascii value of each character in the filename
	bool valid = true;										//Flag to make sure file has a valid format
	bool hasDot = false;									//Flag to make sure file contains a period
	bool goodFile = true;									//Flag to make sure file was read properly
	StackClass path;										//Stack to store paths
	ItemType currentItem;									//Current ItemLocation of the stack
	Location start;											//Entry point of maze
	ofstream outdat(FILE_OUT);								//Stream to write solutions to
	string filename;										//File name to read from
	
	

	//Prompt the user for the file name and store it
	cout << ENTER_FILE << endl;
	cin >> filename;

	//File validation:

	//Check each character in the string
	for (int i = 0; i < filename.length(); i++)
	{

		//Convert each one to an uppercase to simplify the ASCII range
		filename[i] = toupper(filename[i]);

		//Get the current char's ASCII value
		ascii = int(filename[i]);

		//If it contains a period
		if (filename[i] == '.')
		{
			hasDot = true;

			//Must be 3 letters after the period
			if ((i + 3) != (filename.length() - 1))
				valid = false;

		}//end period check
		
		//Range of A-Z values in ASCII
		else if (	ascii < LOWER_ASCII_LIMIT ||
					ascii > UPPER_ASCII_LIMIT)
		{
			valid = false;

		}//end else if
	}

	//If file is valid
	if (valid && hasDot)
	{
		//Create a board from the file
		Board myboard = CreateBoardFromFile(filename, goodFile);
		
		//If file was read properly
		if (goodFile)
		{

			//Prompt user of successful file read
			cout << SUCCESS_STR << endl;
			myboard.Print();

			start.row = myboard.GetHeight() - 1; start.col = myboard.GetLength() - 1;

			//Exit point is blocked
			if (!myboard.IsOpen(start))
			{
				outdat << EXIT_BLOCKED << endl;
				valid = false;

			}//end exit point check

			start.row = 0; start.col = 0;

			//Entry point is blocked
			if (!myboard.IsOpen(start))
			{
				outdat << ENTRY_BLOCKED << endl;
				valid = false;

			}//end entry point check

			//If the board is still valid, find all paths
			if (valid)
			{
				currentItem.loc = start;
				FindPaths(myboard, start, path, counter, outdat, currentItem);

			}//end find all solutions

			//If no paths were found, there are no solutions
			if (counter == 0 && valid)
			{
				outdat << NO_SOLUTIONS << endl;

			}//end no solutions

		}

		//File was not read properly
		else
		{
			cout << FILE_READ_ERR << endl;

		}//end file read error

	}//end valid file


	//File was not valid
	else
	{
		cout << FILE_FORMAT_ERR << endl;

	}//end invalid file

	
}//end main


/***************************************************************************************************/


//pre:  gb is a valid gameboard
//		loc is the a valid starting point w/in gb
//		outdat is a valid output stream
//post:	recursively finds all possible paths for a given board and writes each solution to a given file
//		provided a solution stack
bool FindPaths(	/*inout*/Board &gb,				//board that will track movements
				/*in*/Location loc,				//current location that we are checking
				/*inout*/StackClass &path,		//current solution path stores as a stack
				/*inout*/int &counter,			//current solution number
				/*inout*/ofstream &outdat,		//file stream to write solutions to
				/*inout*/ItemType currentItem)	//current item in the stack
{

	//Current item is the current location, add it to solition stack
	currentItem.loc.row = loc.row; currentItem.loc.col = loc.col;
	path.Push(currentItem);

	//If we are at an exit point, we have a solution
	if ((loc.row == gb.GetHeight() - 1 &&
		loc.col == gb.GetLength() - 1))
	{
		
		counter++;
		WriteSolutionToFile(outdat, path, counter);

	}//end solution


	//If the current space is available
	else if (gb.IsOpen(loc))
	{

		//Set it as marked
		gb.SetOpen(loc, false);

		//South movement
		if (FindPaths(gb, ModifyLocation(loc, SOUTH), path, counter, outdat, currentItem))
			return true;
		
		//East movement
		if (FindPaths(gb, ModifyLocation(loc, EAST), path, counter, outdat, currentItem))
			return true;

		//North movement
		if (FindPaths(gb, ModifyLocation(loc, NORTH), path, counter, outdat, currentItem))
			return true;

		//West movement
		if (FindPaths(gb, ModifyLocation(loc, WEST), path, counter, outdat, currentItem))
			return true;

		//No possible movements, set the space as open, backtrack
		gb.SetOpen(loc, true);
	}


	//Base case: current location is not available
	path.Pop();
	return false;

}


/***************************************************************************************************/


//pre: loc is a valid initalized Location
//post: loc has been modified appropriately given a direction
//		If moving north, row is decremented
//		If moving south, row is incremented
//		If moving east, col is incremented
//		If moving west, col is decremented
//		The modified location has been returned to the caller

/*out*/ Location ModifyLocation						//Modified location to return to caller
						(/*in*/Location loc,		//The given location to be modified 
						/*in*/Direction direction)	//Desired direction of movement
{
	switch (direction)
	{
	case NORTH:
		loc.row--;
		break;

	case SOUTH:
		loc.row++;
		break;

	case EAST:
		loc.col++;
		break;

	case WEST:
		loc.col--;
		break;

	}//end switch

	return loc;

}//end ModifyLocation


/***************************************************************************************************/


//pre: outdat has been bound to an output file
//		solution is a valid StackClass containing a solution path
//		solutionNum is the current number of solutions for the board
//post: The solution contained in StackClass has been written to outdat
void WriteSolutionToFile(	/*inout*/ofstream &outdat, //output file to be written to
							/*in*/StackClass solution, //solution stack. passed by copy to 
													   //preserve the original stack
							/*in*/int solutionNum)	   //current solution number
{

	

	ItemType current, next;			//Used to compare current and next stack items
	StackClass reverse;				//Stack initally is 'backwards'

	//get the soltion in the correct order
	while (!solution.IsEmpty())
	{
		reverse.Push(solution.Retrieve());
		solution.Pop();

	}//end while

	solution = reverse;


	//Write the path to the file
	outdat << PATH_NUM << solutionNum << endl;
	outdat << START << endl;

	//While the solution stack is not empty, compare each location to see which direction it moved
	while (!solution.IsEmpty())
	{
		current = solution.Retrieve();
		solution.Pop();
		if (!solution.IsEmpty())
		{
			next = solution.Retrieve();
			if (current.loc.row < next.loc.row)
				outdat << SOUTH_STR;
			else if (current.loc.row > next.loc.row)
				outdat << NORTH_STR;
			else if (current.loc.col < next.loc.col)
				outdat << EAST_STR;
			else if (current.loc.col > next.loc.col)
				outdat << WEST_STR;
			outdat << endl;

		}//end if
		
	}//end while

	outdat << END << endl << endl;

}//end WriteSolutionToFile


/***************************************************************************************************/


//pre: fileIn is a properly formatted maze file. The file at minimum contains the dimensions of the board
//post: a new Board is returned to the caller. The board has been initialized and walls 
//		have been set appropriately
/*out*/Board CreateBoardFromFile(							//Board to be returned to the caller
								/*in*/string fileIn,		//file name of the maze file
								/*inout*/bool &goodFile)	//boolean passed by ref 
															//representing a bad file read
{
	fstream indat;		//In file
	Location loc;		//Location of walls
	int row, col;		//coordinates

	indat.open(fileIn.c_str());

	//If the file was properly opened
	if (indat.good())
	{

		indat >> row;
		indat >> col;

		if (row <= 0 || col <= 0)
			goodFile = false;

		Board board(row, col);

		//?? Not working with a single line file without .eof()
		//While we are not at the end of the file
		while (!indat.eof())
		{
			indat >> loc.row;
			indat >> loc.col;

			board.SetOpen(loc, false);
		}

		return board;
	}
	
	//File was not read properly
	else
		goodFile = false;

	indat.close();

}//end CreateBoardFromFile


/***************************************************************************************************/

/*
Author: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Cell.h
Purpose: Provides the specification for a Cell structure. A cell is either blocked off (wall),
			visited (maze path has been to this cell) or not visited. 
*/


struct Cell
{
	//Regardless if a given cell is out of bounds, a wall, or visited it is not accessable
	bool open;	

};
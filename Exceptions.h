/*
Author: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Exceptions.h
Purpose: Provides exceptions used in this project
*/

//Thrown when the stack cannot allocate another node due to no memory left on the heap
class OutOfMemoryException{};

//Thrown when the caller attempts to retrieve an item on an empty stack
class RetrieveOnEmptyException{};
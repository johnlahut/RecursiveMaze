/*
Author: Luke Musto
Modifications: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Stack.cpp
Purpose: Provides the implementation for a linked based Stack class storing StackItem
*/



//IMPLEMENTATION FILE : stack.cpp
// This file contains the implementation of a dynamically allocated stack.

#ifndef STACK_H
#define STACK_H


#include "Exceptions.h"
#include "Stack.h"
#include "ItemType.h"

#include<iostream>
using namespace std;

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

StackClass();
Default constructor, creates an empty stack

StackClass(const StackClass& orig);
Copy constructor. Applying stack is identical to orig

~StackClass();
Destructor. Stack is deallocated from memory

bool IsEmpty();
Returns true if the stack is empty, false otherwise

bool IsFull();
Returns false to the caller. Stack is never full.

void Push(StackItem newItem);
Pushes a new StackItem onto the stack. Item is now at the top of the stack.

void Pop();
Top of the stack is removed

StackItem Retrieve();
Returns the top of the stack to the caller. Stack remains unchanged.

void Clear();
Removes all items from the stack. Stack is now empty.

void Print();
Prints the stack to the console. Used for testing purposes.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Protected Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

node* Allocate();
Creates a new node and returns it to the caller. Throws an OutOfMemoryException if heap is out of memory
*/



/******************************************************************************************************/



//***************************************************************************
//*																			*
//*				declare struct from forward declaration						*
//*																			*
//***************************************************************************
struct node
{
	ItemType data;
	node* next;
};



//***************************************************************************
//*																			*
//*				constructors, destructor, and copy constructor				*
//*																			*
//***************************************************************************

//Default constructor
//pre: none
//post: Stack has been initalized
StackClass::StackClass()
{

	head = nullptr;

}  // end default constructor


/******************************************************************************************************/


//Copy constructor
//pre: orig is a valid StackClass
//post: A deep copy of orig has been created
StackClass::StackClass(const StackClass& orig)
{

	head = nullptr;
	operator=(orig);

} // end copy constructor



//Destructor
//pre: StackClass has been initialized
//post: StackClass has been decallocated from memory
StackClass::~StackClass()
{
	Clear();

}//end Destructor


//***************************************************************************
//*																			*
//*				observer predicators										*
//*																			*
//***************************************************************************

//pre: StackClass has been initialized
//post: Returns true to the caller if stack is empty, false otherwise
/*out*/bool StackClass::IsEmpty() const					//boolean value is returned to the caller
{
	return(head == nullptr);

}//end IsEmpty


/******************************************************************************************************/


//pre: StackClass has been initialized
//post: Returns true to the caller if the stack is full, false otherwise
/*out*/bool StackClass::IsFull() const					//boolean value is returned to the caller
{
	return false;

}//end IsFull


//***************************************************************************
//*																			*
//*				observer accesor											*
//*																			*
//***************************************************************************


//pre: StackClass has been initialized, StackClass contains at least one element
//post: Top of the stack has been returned to the caller. Stack remains unchanged. 
//Exceptions thrown: RetrieveOnEmptyException is thrown if the caller attempts to 
//			Retrieve an item on an empty stack
/*out*/ItemType StackClass::Retrieve() const		//StackItem is the item being returned to the caller
//														(top of stack)
{
	if (!IsEmpty())
		return head->data;

	throw RetrieveOnEmptyException();

}//end Retrieve




//***************************************************************************
//*																			*
//*							Mutators										*
//*																			*
//***************************************************************************



//pre: StackClass has been initialized, newItem is a valid StackItem
//post: StackItem has been added to the top of the stack 
void StackClass::Push(/*in*/ItemType newItem)			//newItem is a valid StackItem
{
	if (IsEmpty())
	{
		head = Allocate();

	}//end if

	else
	{
		node *temp = head;
		head = Allocate();
		head->next = temp;

	}//end else

	head->data = newItem;

}//end Push


/******************************************************************************************************/


//pre: StackClass has been initialized
//post: The top of the stack has been removed and deallocated from memory
void StackClass::Pop()
{
	if (!IsEmpty())
	{
		node *temp = head;
		head = head->next;
		delete temp;

	}//end if

}//end Pop


//pre: StackClass has been initialized
//post: StackClass has been restored to its initial state
void StackClass::Clear()
{
	while (!IsEmpty())
		Pop();

}//end Clear


/******************************************************************************************************/


//pre: StackClass has been initialized, orig is a valid StackClass
//post: Applying object is now identical to orig
void StackClass::operator=(/*in*/const StackClass& orig)	//Right hand object
{
	StackClass temp;
	node *current = orig.head;
	Clear();						//Clear the current list


	//Copies the list twice to preserve order of the original list

	while (current != nullptr)
	{
		temp.Push(current->data);
		current = current->next;

	}//end while

	while (!temp.IsEmpty())
	{
		Push(temp.Retrieve());
		temp.Pop();

	}//end while

}//end operator=


/******************************************************************************************************/


//protected method

//pre: StackClass has been initalized
//post: Returns a new node pointer to the caller that has had its values initalized (nullptrs)
/*out*/node* StackClass::Allocate()					//Node pointer is returned to the caller
{
	try
	{
		node *temp = new node;
		temp->next = nullptr;
		return temp;

	}//end try

	catch (bad_alloc*)
	{
		throw new OutOfMemoryException;

	}//end catch

}//end Allocate



/******************************************************************************************************/


#endif





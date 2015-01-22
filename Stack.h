/*
Author: Luke Musto
Modifications: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: Stack.cpp
Purpose: Provides the specification for a linked based Stack class storing StackItem
*/
//
//  
// 
//***************************************************************************
//  The public methods are: 
//    StackClass();  		: prepares stack for usage.	
//
//	  ~StackClass();    	: returns all dynamically allocated memory to heap	
//
//	  StackClass(const StackClass& orig);  : creates a deep copy of the object 	
//		
//    bool IsEmpty() const : returns true if stack has no elements. 
//
//    bool IsFull() const  : returns true if stack has no empty spaces.
//
//    void Push(ItemType newItem);	adds newItem to top of stack
//
//    void Pop();		Removes top item from stack.
//
//    ItemType Retrieve() const;  returns item at top of stack		
//		 DOES NOT REMOVE TOP ELEMENT!!!!  STACK IS UNCHANGED!!!
//	 
//	  void Clear();
//
//	  virtual void operator =(const StackClass& orig);
//
//**********************************************************************************

#include"ItemType.h"

//forward declaration of struct

struct node;

//class declaration
class StackClass

{
public:

	//Default constructor
	//pre: none
	//post: Stack has been initalized
	StackClass();

	/******************************************************************************************************/

	//Copy constructor
	//pre: orig is a valid StackClass
	//post: A deep copy of orig has been created
	StackClass(/*in*/const StackClass& orig);	//orig is a valid StackClass object

	/******************************************************************************************************/

	//pre: StackClass has been initialized
	//post: StackClass has been decallocated from memory
	~StackClass();

	/******************************************************************************************************/

	//pre: StackClass has been initialized
	//post: Returns true to the caller if stack is empty, false otherwise
	/*out*/bool IsEmpty() const;						//boolean value is returned to the caller

	/******************************************************************************************************/

	//pre: StackClass has been initialized
	//post: Returns true to the caller if the stack is full, false otherwise
	/*out*/bool IsFull() const;						//boolean value is returned to the caller

	/******************************************************************************************************/

	//pre: StackClass has been initialized, newItem is a valid StackItem
	//post: StackItem has been added to the top of the stack 
	void Push(/*in*/ItemType newItem);			//newItem is a valid StackItem

	/******************************************************************************************************/

	//pre: StackClass has been initialized
	//post: The top of the stack has been removed and deallocated from memory
	void Pop();

	/******************************************************************************************************/

	//pre: StackClass has been initialized, StackClass contains at least one element
	//post: Top of the stack has been returned to the caller. Stack remains unchanged. 
	//Exceptions thrown: RetrieveOnEmptyException is thrown if the caller attempts to 
	//			Retrieve an item on an empty stack
	/*out*/ItemType Retrieve() const;				//StackItem is the item being returned to the caller 
	//												(top of stack)

	/******************************************************************************************************/

	//pre: StackClass has been initialized
	//post: StackClass has been restored to its initial state
	void Clear();

	/******************************************************************************************************/

	//pre: StackClass has been initialized, orig is a valid StackClass
	//post: Applying object is now identical to orig
	virtual void operator=(/*in*/const StackClass& orig);	//Right hand object

	/******************************************************************************************************/

	//pre: StackClass has been initalized
	//post: StackClass has been printed to the console
	void Print();


protected:


	//pre: StackClass has been initalized
	//post: Returns a new node pointer to the caller that has had its values initalized (nullptrs)
	/*out*/node* Allocate();					//Node pointer is returned to the caller


private:

	//External pointers of the object.

	node* head;		//Points to the top of the stack


}; // end StackClass
/*
Author: John Lahut
Date: 11.5.2014
Project: TheMaze
Filename: ItemType.h
Purpose: Provides the specification for a StackItem. A StackItem is what we are storing in our stack.
Current stack is storing a location
*/

#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include "Location.h"

struct ItemType
{
	Location loc;			//Location to store. Location is defined in the Location.f file

};

#endif
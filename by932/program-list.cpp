/********************************
*Filename:program-list.cpp	*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include "program-list.h"
using namespace std;
// constructor
LIST::LIST()
{
	head = NULL;

}

//deconstructor
LIST::~LIST()
{
	node* temp = head;
	while(temp && temp->next)
	{
		temp=temp->next;
		delete temp;	//delet linked-list
	}
}

bool LIST::load(char token[], int line)
{

	if (head == NULL)	// linked list is empty - so this will be the head node
	{			

		NPtr newnode = new node;

		if (newnode == NULL)		// could not allocate memory
		{
			cout << "Allocation error occured" << endl;
			return false;
		}	
		strcpy(newnode->content, token);
		newnode->line = line;
		newnode->next = NULL;
		head = newnode;
		
	}
	else		// if not here then the linked list exists
	{
		NPtr check = head;
		while (check != NULL)
		{			
			if (check->next == NULL)
			{					
				NPtr newnode = new node;
				if (newnode == NULL)
				{
					cout << "Allocation error occured" << endl;
					return false;
				}
				strcpy(newnode->content, token);	//store token
				newnode->line = line;	//give the line number
				newnode->next = NULL;	//new node next node = null
				check->next = newnode;
				break;
			}
			check = check->next;
			
		}
	}
	return true;
	
}

bool LIST::print(ostream&)
{
	cout << "Start output Part 1" << endl;
	if (head == NULL)
	{
		return false;
	}
	NPtr temp = head;				// do not change the head pointer
	while (temp != NULL)
	{
		//cout << "token = " << temp->content << '\t' << "line_num = " << temp->line;
		//cout << endl;
		temp = temp->next;
	}
	cout << "End output Part 1" << endl;
	return true;

}

/********************************
*Filename:linkedlist.cpp	*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include "linkedlist.h"
using namespace std;
int listdatacmp(const T& a, const T& b)			// user defined compare function
{
		// return < 0 if a < b
		// return == 0 if a == b
		// return >0 if a > b;
		
		return 0;
}

// iterator methods

void linkedlist::setiterator()
{
    iterator_current = head;
}

// is there more in the iterator

bool linkedlist::more()
{
    if (iterator_current != NULL)
        return true;
    else
        return false;
}

// get next piece of data out of iterator

T linkedlist::next()
{
    T tmp = iterator_current->data;
    iterator_current = iterator_current->next;
    return tmp;
}

void linkedlist::insertbeforecurrent(const T& newdata)			// insertion method
{
	nodeptr tmp;
	tmp = new node;
	tmp->data = newdata;
	tmp->next = NULL;

	nodeptr curr;
	nodeptr prev;
	curr = head;
	prev = NULL;

	while (curr != iterator_current)
	{
		prev = curr;
		curr = curr->next;
	}

	if (prev == NULL)
		head = tmp;
	else
		prev->next = tmp;
	tmp->next = curr;
}

bool linkedlist::deletecurrent(T& retdata)		
{
	nodeptr curr;
	nodeptr prev;
	curr = head;
	prev = NULL;
	
        if (iterator_current == NULL)
            return false;

	while (curr != iterator_current)		// find it
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL)
	{
		return false;
	}

	if (prev)
	{
		prev->next = curr->next;
		retdata = curr->data;
		delete curr;
		return true;
	}
	else
	{
		head = curr->next;
		retdata = curr->data;
		delete curr;
		return true;
	}
}

// constructor
linkedlist::linkedlist()
{
	head = NULL;
}
//deconstructor
linkedlist::~linkedlist()
{
	node* temp = head;
	while(temp && temp->next)
	{
		temp=temp->next;
		delete temp;	//delet linked-list
	}
} 			
// add to tail method
void linkedlist::addtotail(char token[], int line_no)
{
	nodeptr tmp, curr;
	tmp = new node;
	tmp->data.content = token;
	tmp->data.line_num = line_no;
	tmp->next = NULL;

	if (head != NULL)
	{
		curr = head;
		while (curr->next)
			curr = curr->next;
		curr->next = tmp;
	}
	else
		head = tmp;
}

// check if list is empty method
bool linkedlist::isempty()
{
	if (head == NULL)
		return true;
	else
		return false;
}

// remove from head method
T linkedlist::removefromhead()
{
	nodeptr tmp;
	T data;
	
	data = head->data;
	tmp = head;
	head = head->next;
	delete tmp;
	return data;
}

void linkedlist::insert(const T& newdata)			// insertion method
{
	nodeptr tmp;
	tmp = new node;
	tmp->data = newdata;
	tmp->next = NULL;

	nodeptr curr;
	nodeptr prev;
	curr = head;
	prev = NULL;

	while (curr && listdatacmp(newdata, curr->data) >= 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (prev == NULL)
		head = tmp;
	else
		prev->next = tmp;
	tmp->next = curr;


}

bool linkedlist::locate(const T& keydata, T& retresult)		// locate method
{
	nodeptr curr = head;

	while (curr && listdatacmp(keydata, curr->data) != 0)
	{
		curr = curr->next;
	}

	if (curr == NULL)
		return false;
	else
	{
		retresult = curr->data;
		return true;
	}
}

bool linkedlist::delete_node(const T& keydata, T& retdata)		// delete node method
{
	nodeptr curr;
	nodeptr prev;
	curr = head;
	prev = NULL;
	
	while (curr != NULL && listdatacmp(keydata, curr->data) != 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL)
	{
		return false;
	}

	if (prev)
	{
		prev->next = curr->next;
		retdata = curr->data;
		delete curr;
		return true;
	}
	else
	{
		head = curr->next;
		retdata = curr->data;
		delete curr;
		return true;
	}
}
bool linkedlist::print(ostream&)
{
	if (head == NULL)
	{
		return false;
	}
	nodeptr temp = head;				// do not change the head pointer
	while (temp != NULL)
	{
		cout << "token = " << temp->data.content << '\t' << "line_num = " << temp->data.line_num;
		cout << endl;
		temp = temp->next;
	}
	return true;

}

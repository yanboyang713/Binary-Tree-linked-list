/********************************
*Filename:linkedlist.h		*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
using namespace std;

struct linkedlist_node
{
	char *content;
	int line_num;	//story line number
};

typedef linkedlist_node T;



class linkedlist
{
	public:	// public methods
		linkedlist();
		~linkedlist();
		// the destructor has been removed - when you need to delete you must do by hand
		void addtotail(char [], int);
		bool print(ostream&);	//Print out the linked-list
		
		
		bool isempty();
		T removefromhead();
		void insert(const T&);
		bool locate(const T&, T&);
		bool delete_node(const T&, T&);
		
		bool deletecurrent(T&);
		void insertbeforecurrent(const T&);
		void setiterator();
		T next();
		bool more();
	private:	// node data and declaration - hidden in class
		struct node;
		typedef node* nodeptr;
		nodeptr iterator_current;
		struct node
		{
			T data;
			nodeptr next;
		};
		nodeptr head;
};	


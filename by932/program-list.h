/********************************
*Filename:program-list.h	*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include <cstring>
using namespace std;
struct node
{
	char content[40];
	int line;
	node *next;
};
typedef node* NPtr;
class LIST 
{  
 	public: 
  		LIST();      
  		~LIST();     
  		bool load(char[], int); 
  		bool print(ostream&);
	private:  
	  	NPtr head;    // pointer to list of chars
	  	NPtr next;
};

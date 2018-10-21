/********************************
*Filename:program.h		*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include "program-list.h"
using namespace std;

class program 
{  
 	public:
 		
  		program();
                ~program();
                bool open(char[]);			// open a file return state i.e. success
		bool getline(LIST&);
			
	private:
		ifstream fin;
		int line_no;
}; 



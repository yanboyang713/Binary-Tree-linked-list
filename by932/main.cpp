/********************************
*Filename:main.cpp		*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include "program.h"
using namespace std;

int main()
{
	program test_program_class;
	LIST test_list_class;
	
	test_program_class.getline(test_list_class);
	test_list_class.print(cout);
	return 0;
}

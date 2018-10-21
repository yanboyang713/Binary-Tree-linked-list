#include <string>
#include <fstream>
#include <iostream>

// you may need to include your own headers. This is a sample for the program
// class which you may consider.

// PLEASE NOTE THAT THIS IS A SAMPLE OF THE CLASS

using namespace std;

class program
{
        public:
                program();
                ~program();
                int open(char[]);					// open a file return state i.e. success
				int getline(proglinkedlist&);		// return a line of tokens.
        private:
				ifstream ins;
				int line_no;
};

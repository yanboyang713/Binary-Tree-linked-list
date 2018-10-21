/*
	Assignment Four Solution

	This is the solution for assignment four, it uses the class
	program to parse the input and insert ovbjects into a map

	Daniel F. Saffioti
	School of IT and CS
	University of Wollongong

	Sun Oct 20 19:51:11 EST 2002
*/

#include <iostream>
#include <list>
#include <map>
#include <set>
#include "program.h"
using namespace std;

void obtain_input(map<string, set<int> >& mymap);		// function to parse input, puts data into list and map
void output(map<string, set<int> >& mymap, const int res);	// void output before reserved
void pop_reserved(set<string>& rword);				// populates reserved word map
void print(map<string, set<int> >::iterator& mapit);		// print the map
const int RESERVED = 0;
const int NORESERVED = 1;
const int RWORD_MAX = 62;

int main()
{

	map<string, set<int> > mymap;

	obtain_input(mymap);

	cout << "Outputing the key/ data pairs (NOT RESERVED)" << endl;
	output(mymap, RESERVED);

	cout << "Outputing the key/ data pairs (NO RESERVED WORDS)" << endl;
	output(mymap, NORESERVED);

	return 0;
}

// populates reserved words;

void pop_reserved(set<string>& rword)
{
	string reserved[RWORD_MAX]= {"asm", "auto", "bool", "break", "case", "catch", "char", "class", "const" \
	"const_cast", "continue", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "extern" \
	"false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
	"mutable", "namespace", "new", "operator", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static"\
	"static_cast", "struct", "switch", "template", "this", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while"};

	for (int i = 0; i < RWORD_MAX; i++)
		rword.insert(reserved[i]);
}

// function prints out tokens in order

void output(map<string, set<int> >& mymap, const int res)
{
	map<string, set<int> >::iterator mapit = mymap.begin();
	set<string> rword;

	if (res == NORESERVED)
		pop_reserved(rword);

	while (mapit != mymap.end())
	{
		if (res == NORESERVED)
		{
			set<string>::iterator rwordit;
			rwordit = rword.find(mapit->first);
			if (rwordit == rword.end())
			{
				print(mapit);
			}
			mapit++;

		}
		else
		{
			print(mapit);
			mapit++;
		}
	}
}

// print out key/data pair

void print(map<string, set<int> >::iterator& mapit)
{
		cout << mapit->first << "\t";

		set<int>::iterator setit = mapit->second.begin();

		while (setit != mapit->second.end())
		{
			cout << *setit << " ";
			setit++;
		}
		cout << endl;
}

// function puts tokens into a map

void obtain_input(map<string, set<int> >& mymap)
{
	// make instance of class and open the files

	list<string> mylist;
	program parser;
	parser.open();
	int lineno = parser.getline(mylist);

	// get lines of input and insert into the map
	
	do
	{
		if (lineno == -1)
			break;

		list<string>::iterator p = mylist.begin();

		while (p != mylist.end())
		{
			string key = *p;

			// put the key and the data in the map

			map<string, set<int> >::iterator mapit;
			mapit = mymap.find(key);

			if (mapit == mymap.end())
			{
				// key does not already exists in map

				pair<string, set<int> > keydata;
				keydata.first = key;
				keydata.second.insert(lineno);
				mymap.insert(keydata);

			}
			else
			{
				// key already exists in map

				mapit->second.insert(lineno);
			}

			p++;
		}
		mylist.clear();
		lineno = parser.getline(mylist);
	} while (lineno != -1);
}

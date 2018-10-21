/********************************
*Filename:program.cpp		*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include "program.h"
#include "binarytree.h"
using namespace std;
//Global Data 
BinaryTree WordTree;

bool bonus(char []);//delete 62 reserved words
program::program()
{
	line_no = 1;	//init line_no

}
program::~program()
{
	fin.close();	//close the file
}

bool program::open(char source_file[])
{
	
	fin.open(source_file);	//open file
	
	if(!fin)
	{
		cout << "Cann't find file"<< endl;
		return false;	// open file false
	}
	return true;	//open file good

}

bool program::getline(LIST& obj)
{
	char fname[100], token[40], ch;
	int line_pos, carryon, i;
	
	cout << "Enter a filename: ";
	cin >> fname;

	bool good_or_bad = true;	//open file status good or bad, true is good
	good_or_bad = open(fname);

	if (good_or_bad == true)
	{
		line_pos = 0;
		token[0] = 0;		// initialise token	
	
		ch = fin.get();	
		while (!fin.eof())
		{
			//Eating all comments
			if (ch == '/')
			{
				ch = fin.get();	
				line_pos++;
				//"//"type comment - eat both characters and all to newline
				if (ch == '/')
				{
					do
					{
						ch = fin.get();	
					} while (ch != '\n');
					line_no++;
					line_pos = 0;
					ch = fin.get(); // now positioned at start of next line
				}
				//old type comment/* */ - eat both characters and all to end
				else if (ch == '*')
				{
					carryon = 1;
					ch = fin.get();	
					while (carryon)
					{
						if (ch == '\n')
						{
							line_no++;
							line_pos = 0;
							ch = fin.get();	
						}
						else if (ch == '*')
						{
							ch = fin.get();	
							if (ch == '/')
								carryon = 0;
						}
						else
							ch = fin.get();
					}
					ch = fin.get();
					line_pos = 1;					
				}
			}
			else if (ch == '"')
			{
			//character string constant - eat all characters to other end
			//avoiding \anything
				ch = fin.get();
				while (ch != '"')
				{
					if (ch == '\\')
						ch = fin.get();
					ch = fin.get();
				}
				ch = fin.get();
			}
			else if (ch == '\'')
			{
				//character constant - as for character string
				ch = fin.get();
				while (ch != '\'')
				{
					if (ch == '\\')
						ch = fin.get();
					ch = fin.get();
				}
				ch = fin.get();
			}
			else if (line_pos == 0 && ch == '#')
			{
				//# pre-processor line - eat # and all to newline
				do
				{
					ch = fin.get();
				} while (ch != '\n');
				ch = fin.get();
				line_no++;
				line_pos = 0;	
			}
			else if (isalpha(ch))	// start of token
			{
				i = 0;
				do
				{
					
					token[i++] = ch;
					ch = fin.get();
				} while (isalnum(ch) || ch == '_');
				token[i] = 0;	//token end
				bool jud = true;
				jud = bonus(token);	//delete 62 reserved words
				if (jud == false)
					continue;
				//This is part 1
				obj.load(token,line_no);//store token and line number to the list
				
				//This is part 2
				bnode *temp = new bnode;
				temp->content = token;
				temp->line_num = line_no;
				temp->data.addtotail(token, line_no);
				linked_list foundData;
				
				if (WordTree.Locate(temp, foundData))
				{
					//This part is store same line token to the linked-list
					foundData->line_num = line_no;
					foundData->data.addtotail(token, line_no);
					delete temp;
				}
				else
				{
					//This is set up a new tree node
					WordTree.Insert(temp);
				}
 
 
				token[0] = 0;	// initialise token
			}
			else if (ch == '\n')	// just a newline
			{
				line_no++;
				line_pos = 0;
				ch = fin.get();
			}
			else
				ch = fin.get();
		}
	}
	return true;

}
//this is part 3
bool bonus(char token[])
{
	if (strcmp(token, "asm") == 0 ||
	strcmp(token, "casecatch") == 0 ||
	strcmp(token, "const_cast") == 0 ||
	strcmp(token, "do") == 0 ||
	strcmp(token, "enum") == 0 ||
	strcmp(token, "float") == 0 ||
	strcmp(token, "if") == 0 ||
	strcmp(token, "mutable") == 0 ||
	strcmp(token, "private") == 0 ||
	strcmp(token, "reinterpret_cast") == 0 ||
	strcmp(token, "sizeof") == 0 ||
	strcmp(token, "switch") == 0 ||
	strcmp(token, "true") == 0 ||
	strcmp(token, "typename") == 0 ||
	strcmp(token, "virtual") == 0 ||
	strcmp(token, "while") == 0 ||
	strcmp(token, "auto") == 0 ||
	strcmp(token, "char") == 0 ||
	strcmp(token, "continue") == 0 ||
	strcmp(token, "double") == 0 ||
	strcmp(token, "explicit") == 0 ||
	strcmp(token, "for") == 0 ||
	strcmp(token, "inline") == 0 ||
	strcmp(token, "namespace") == 0 ||
	strcmp(token, "protected") == 0 ||
	strcmp(token, "return") == 0 ||
	strcmp(token, "static") == 0 ||
	strcmp(token, "template") == 0 ||
	strcmp(token, "try") == 0 ||
	strcmp(token, "union") == 0 ||
	strcmp(token, "void") == 0 ||
	strcmp(token, "bool") == 0 ||
	strcmp(token, "class") == 0 ||
	strcmp(token, "default") == 0 ||
	strcmp(token, "dynamic_cast") == 0 ||
	strcmp(token, "extern") == 0 ||
	strcmp(token, "friend") == 0 ||
	strcmp(token, "int") == 0 ||
	strcmp(token, "new") == 0 ||
	strcmp(token, "public") == 0 ||
	strcmp(token, "short") == 0 ||
	strcmp(token, "static_cast") == 0 ||
	strcmp(token, "this") == 0 ||
	strcmp(token, "typedef") == 0 ||
	strcmp(token, "unsigned") == 0 ||
	strcmp(token, "volatile") == 0 ||
	strcmp(token, "break") == 0 ||
	strcmp(token, "const") == 0 ||
	strcmp(token, "delete") == 0 ||
	strcmp(token, "else") == 0 ||
	strcmp(token, "false") == 0 ||
	strcmp(token, "goto") == 0 ||
	strcmp(token, "long") == 0 ||
	strcmp(token, "operator") == 0 ||
	strcmp(token, "register") == 0 ||
	strcmp(token, "signed") == 0 ||
	strcmp(token, "struct") == 0 ||
	strcmp(token, "throw") == 0 ||
	strcmp(token, "typeid") == 0 ||
	strcmp(token, "using") == 0 ||
	strcmp(token, "wchar_t") == 0)
		return false;
		
	return true;
	
}

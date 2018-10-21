#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	char fname[100], token[40], ch;
	ifstream fin;
	int line_no, line_pos, carryon, i;
	
	cout << "Enter a filename: ";
	cin >> fname;
	
	fin.open(fname);	
	line_no = 1;
	line_pos = 0;
	token[0] = 0;		// initialise token	
	ch = fin.get();	
	while (!fin.eof())
	{
		if (ch == '/')
		{
			ch = fin.get();	
			line_pos++;
			if (ch == '/')
			{
//				// type comment - eat both characters and all to newline
				do
				{
					ch = fin.get();	
				} while (ch != '\n');
				line_no++;
				line_pos = 0;
				ch = fin.get(); // now positioned at start of next line
			}
			else if (ch == '*')
			{
//				old type comment - eat both characters and all to end
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
//			character string constant - eat all characters to other end
//			avoiding \anything
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
//			character constant - as for character string
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
//			# pre-processor line - eat # and all to newline
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
			token[i] = 0;
			printf("%d: %s\n",line_no,token);
			token[0] = 0;
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
	fin.close();

	return 0;
}

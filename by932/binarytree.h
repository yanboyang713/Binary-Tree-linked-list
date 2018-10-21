/********************************
*Filename:binarytree.h		*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include <cstring>
#include "linkedlist.h"
using namespace std;
// Definition of data contained in BinaryTree
struct bnode
{
	linkedlist data;	//store token
	int line_num;	//story line number
	char *content;	//token content[40];
};

typedef bnode * linked_listPtr;

typedef linked_listPtr linked_list;


class BinaryTree
{	
	public:
		BinaryTree();//constructor
		~BinaryTree();// destructor
		void Insert(const linked_list&);
		bool Locate(const linked_list&, linked_list&);
		bool Delete(const linked_list&, linked_list&);
		
		// iterator methods
		void SetIterator();		// find left most node
		linked_list Next();		// return next data item
		bool More();			// are there any more nodes?
		
	private:
		struct TreeNode
		{
			linked_list data;
			TreeNode *left, *right, *parent;
		};

		TreeNode* root;
		TreeNode* curr;				// used by iterator
		
		TreeNode* FindNode(const linked_list&, TreeNode*);
		void InsertNode(const linked_list&, TreeNode*&);
	//this function is given the root node and will do a post order deletion of the nodes
		void postorderdelete(TreeNode*);
};



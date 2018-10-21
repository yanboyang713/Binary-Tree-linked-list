/********************************
*Filename:binarytree.cpp	*
*Login:by932			*								
*AssignmentNo:ass5		*
*DateLastModified:2/11/2014	*							
********************************/
#include <iostream>
#include "binarytree.h"
using namespace std;

int TreeDataCmp(const linked_list& first, const linked_list& second)
{
	if (first->line_num < second->line_num)
		return -1;
	if (first->line_num == second->line_num)
		return 0;
	if (first->line_num > second->line_num)
		return 1;
	return 0;
}

BinaryTree::BinaryTree()
{
	root = NULL;
}
BinaryTree::~BinaryTree()
{
	postorderdelete(root);
}
void BinaryTree::postorderdelete(TreeNode* curr)
{
	if (curr != NULL)
	{
		postorderdelete(curr->left);
		postorderdelete(curr->right);
		
		delete curr;
	}
}
void BinaryTree::SetIterator()
{
	curr = root;
	if (curr != NULL)
		while (curr->left != NULL)
			curr = curr->left;
}

linked_list BinaryTree::Next()
{
	linked_list rvalue = curr->data;

	if (curr->right != NULL)	// into the right subtree
	{
		curr = curr->right;
		while (curr->left != NULL)
			curr = curr->left;
	}
	else if (curr->parent == NULL)	// no parent
		curr = NULL;		// we are finished
	else				// find ancestor
	{
		while (curr->parent != NULL
				&& (curr->parent)->left != curr)
			curr = curr->parent;
		curr = curr->parent;
	}
	return rvalue;
}		


bool BinaryTree::More()
{
	if (curr != NULL)
		return true;
	else
		return false;
}	



void BinaryTree::Insert(const linked_list& data)
{
	InsertNode(data, root);
}

bool BinaryTree::Locate(const linked_list& data, linked_list& founddata)
{
	TreeNode* foundNode = FindNode(data, root);
	
	if (foundNode != NULL)
	{
		founddata = foundNode->data;
		return true;
	}
	else
		return false;

}

bool BinaryTree::Delete(const linked_list& data, linked_list& deldata)
{
	TreeNode *parent, *prev, *curr = FindNode(data, root);
	
	if (curr == NULL)
		return false;
	deldata = curr->data;
	parent = curr->parent;
	if (curr->left == NULL)			// no left subtree
	{
		if (curr->right == NULL)	// no children
		{
			if (parent == NULL)	// curr is root
				root = NULL;
			else if (parent->left == curr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else				// only right subtree
		{
			if (parent == NULL)
			{
				root = curr->right;
				root->parent = NULL;
			}
			else if (parent->left == curr)
			{
				parent->left = curr->right;
				curr->right->parent = parent;
			}
			else
			{
				parent->right = curr->right;
				curr->right->parent = parent;
			}
		}
	}
	else if (curr->right == NULL)		// only left subtree
	{
		if (parent == NULL)
		{
			root = curr->left;
			root->parent = NULL;
		}
		else if (parent->left == curr)
		{
			parent->left = curr->left;
			curr->left->parent = parent;
		}
		else
		{
			parent->right = curr->left;
			curr->left->parent = parent;
		}
	}
	else				// has both subtrees
	{
		prev = curr->left;
		while (prev->right != NULL)
			prev = prev->right;
		prev->right = curr->right;
		curr->right->parent = prev;
		if (parent == NULL)
		{
			root = curr->left;
			root->parent = NULL;
		}
		else
		{
			parent->right = curr->left;
			curr->left->parent = parent;
		}
	}
	delete curr;
	return true;
}


BinaryTree::TreeNode* BinaryTree::FindNode(const linked_list& data, BinaryTree::TreeNode* tree_root)
{
	if (tree_root == NULL)
	{
		return 0;
	}	
	int Result = TreeDataCmp(data,tree_root->data);

	if (Result == 0)
		return tree_root;
	if (Result < 0 && tree_root->left != NULL)
		return FindNode(data,tree_root->left);
	else if (Result > 0 && tree_root->right != NULL)
		return FindNode(data,tree_root->right);
	return 0;
}


void BinaryTree::InsertNode(const linked_list& data, BinaryTree::TreeNode*& tree_root)
{
	//insert root node
	if (tree_root == NULL)
	{
		tree_root = new TreeNode;	//set up a new node
		tree_root->data = data;
		tree_root->left = NULL;
		tree_root->right = NULL;
		tree_root->parent = NULL;
	}
	else if (TreeDataCmp(data,tree_root->data) <= 0)
	{
		if (tree_root->left == NULL)
		{
			tree_root->left = new TreeNode;
			tree_root->left->data = data;
			tree_root->left->left = NULL;
			tree_root->left->right = NULL;
			tree_root->left->parent = tree_root;
		}
		else	
			InsertNode(data,tree_root->left);
	}
	else
	{
		if (tree_root->right == NULL)
		{
			tree_root->right = new TreeNode;
			tree_root->right->data = data;
			tree_root->right->left = NULL;
			tree_root->right->right = NULL;
			tree_root->right->parent = tree_root;
		}
		else	
 			InsertNode(data,tree_root->right);
 	}
}


#include <iostream>
using namespace std;

struct yourtype
{
	// your type;
};

typedef yourtype T;

int TreeDataCmp(const T& a, const T& b)
{
	// implement this 
	// a < b return < 0
	// if a == b return == 0
	// if a > b return > 0
	return 0;
}

class BinaryTree
{	
	public:
		BinaryTree();
		// destructor has been removed - deletion of the entire structure must be done by hand.
		void Insert(const T&);
		bool Locate(const T&, T&);
		bool Delete(const T&, T&);
		
		// iterator methods
		void SetIterator();						// find left most node
		T Next();								// return next data item
		bool More();							// are there any more nodes?	
	private:
		struct TreeNode
		{
			T data;
			TreeNode *left, *right, *parent;
		};

		TreeNode* root;
		TreeNode* curr;							// used by iterator
		
		TreeNode* FindNode(const T&, TreeNode*);
		void InsertNode(const T&, TreeNode*&);
};

void BinaryTree::SetIterator()
{
	curr = root;
	if (curr != NULL)
		while (curr->left != NULL)
			curr = curr->left;
}

T BinaryTree::Next()
{
	T rvalue = curr->data;

	if (curr->right != NULL)			// into the right subtree
	{
		curr = curr->right;
		while (curr->left != NULL)
			curr = curr->left;
	}
	else if (curr->parent == NULL)	// no parent
		curr = NULL;				// we are finished
	else							// find ancestor
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


BinaryTree::BinaryTree()
{
	root = NULL;
}

void BinaryTree::Insert(const T& data)
{
	InsertNode(data, root);
}

bool BinaryTree::Locate(const T& data, T& founddata)
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

bool BinaryTree::Delete(const T& data, T& deldata)
{
	TreeNode *parent, *prev, *curr = FindNode(data, root);
	
	if (curr == NULL)
		return false;
	deldata = curr->data;
	parent = curr->parent;
	if (curr->left == NULL)					// no left subtree
	{
		if (curr->right == NULL)				// no children
		{
			if (parent == NULL)				// curr is root
				root = NULL;
			else if (parent->left == curr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else								// only right subtree
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
	else if (curr->right == NULL)			// only left subtree
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
	else									// has both subtrees
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


BinaryTree::TreeNode* BinaryTree::FindNode(const T& data, BinaryTree::TreeNode* tree_root)
{
	if (tree_root == NULL)
		return 0;
		
	int Result = TreeDataCmp(data,tree_root->data);

	if (Result == 0)
		return tree_root;
	if (Result < 0 && tree_root->left != NULL)
		return FindNode(data,tree_root->left);
	else if (Result > 0 && tree_root->right != NULL)
		return FindNode(data,tree_root->right);
	return 0;
}


void BinaryTree::InsertNode(const T& data, BinaryTree::TreeNode*& tree_root)
{
	if (tree_root == NULL)
	{
		tree_root = new TreeNode;
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


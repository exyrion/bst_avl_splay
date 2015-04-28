//Justin Liang
//CS130A
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>

using namespace std;

class BSTNode
{
	public:
	int element;
	BSTNode *left;
	BSTNode *right;
	
	BSTNode(int x, BSTNode *lt, BSTNode *rt)
	{
		element = x;
		left = lt;
		right = rt;
	}
};


class BST
{
	private:
	BSTNode *root;
	
	public:
	BST()
	{
		root = NULL;
	}
	
	
	//Finds minimum element in subtree n
	BSTNode *findMin(BSTNode *n)
	{
		if(n == NULL)
			return NULL;
		if(n->left == NULL)
			return n;
		return findMin(n->left);
	}
		
	public:
	
	//Insert x into the binary search tree
	void insert(int x)
	{
		insert(x, root);
	}
	
	//Recursive function to insert x into the binary search tree
	void insert(int &x, BSTNode *&n)
	{
		if(n == NULL)
			n = new BSTNode(x, NULL, NULL);
		else if(x < n->element)
			insert(x, n->left);
		else if(x > n->element)
			insert(x, n->right);
		else
			;
	}
	
	//Finds x in the binary search tree
	bool access(int x)
	{
		return access(x, root);
	}
	
	//Recursive function to find x in the binary search tree
	//Returns true if element is in the BST, returns false if it is not
	bool access(int x, 
	BSTNode *n)
	{
		if(n == NULL)
			return false;
		else if(x < n->element)
			return access(x, n->left);
		else if(x > n->element)
			return access(x, n->right);
		else
			return true;
	}
	
	//Removes x in the binary search tree
	void remove(int x)
	{
		remove(x, root);
	}
	
	//Recursive function to remove x in the binary search tree
	void remove(int x, BSTNode *&n)
	{
		if(n == NULL)
			return;
		if(x < n->element)
			remove(x, n->left);
		else if(x > n->element)
			remove(x, n->right);
		else if(n->left != NULL && n->right != NULL) //Case of two children
		{
			n->element = findMin(n->right)->element;
			remove(n->element, n->right);
		}
		else
		{
			BSTNode *temp = n;
			if(n->left != NULL)
				n = n->left;
			else
				n = n->right;
		}
	}
	
	//Prints element using in-order traversal
	void printTree (ostream & out = cout)
	{
		printTreePreOrder(root, out);
		cout << endl;
		printTreeInOrder(root, out);
		cout << endl;
	}
	
	//Recursive function to print subtree rooted at n in sorted order
	void printTreeInOrder (BSTNode *n, ostream & out)
	{
		if(n != NULL)
		{
			printTreeInOrder(n->left, out);
			out << n-> element << " ";
			printTreeInOrder(n->right, out);
		}			
	}
	
	//Recursive function to print subtree rooted at n in pre order
	void printTreePreOrder (BSTNode *n, ostream & out)
	{
		if(n != NULL)
		{			
			out << n-> element << " ";
			printTreePreOrder(n->left, out);
			printTreePreOrder(n->right, out);
		}			
	}
};


//Main function
int main()
{
	BST *b = new BST();
	string str;
	int val;
	cin >> str;
	clock_t start, end;
	start = clock();
	while(!cin.eof())
	{		
		if(str.compare("insert") == 0)
		{
			cin >> val;
			if((b->access(val)) == true)
				cout << "Element already inserted" << endl;
			else
			{
				b->insert(val);
				cout << "Element inserted" << endl;
			}
		}
		
		if(str.compare("access") == 0)
		{
			cin >> val;
			if((b->access(val)) == true)
				cout << "Element accessed" << endl;
			else
				cout << "Element not found" << endl;
		}
		
		if(str.compare("delete") == 0)
		{
			cin >> val;
			b->remove(val);
		}
		
		if(str.compare("print") == 0)
		{
			b->printTree();
		}		
		cin >> str;
		
	}
	end = clock();
	cout << "time took: " << (float(end-start)/(CLOCKS_PER_SEC/1000)) << endl;
	return 0;
}


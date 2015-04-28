//Justin Liang
//CS130A
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>

using namespace std;

//Class AVLNode for the AVL tree, differs from BSTNode since there's a 
class AVLNode
{
	public:
	int element;
	int height;
	AVLNode *left;
	AVLNode *right;
	
	AVLNode(int x, AVLNode *lt, AVLNode *rt)
	{
		element = x;
		left = lt;
		right = rt;
	}
};


class AVL
{
	private:
	AVLNode *root;
	
	
	
	public:
	AVL()
	{
		root = NULL;
	}
	
	
	//Finds minimum element in subtree n
	AVLNode *findMin(AVLNode *n)
	{
		if(n == NULL)
			return NULL;
		if(n->left == NULL)
			return n;
		return findMin(n->left);
	}
	
	//Finds maximum element in subtree n
	AVLNode *findMax(AVLNode *n)
	{
		if(n != NULL)
			while(n->right != NULL)
				n = n->right;
		return n;
	}
	
	//Returns the height of the node n, returns -1 if NULL
	int height(AVLNode *n)
	{
		if(n == NULL)
			return -1;
		else
			return n->height;
	}
		
	//Single rotation with left child
	void singleRotateLeft(AVLNode * & k2)
	{
		AVLNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;		
	}
	
	//Single rotation with right child
	void singleRotateRight(AVLNode * & k1)
	{
		AVLNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->left), k1->height) + 1;
		k1 = k2;		
	}
	
	//Double rotation with left child
	void doubleRotateLeft(AVLNode * & k3)
	{
		singleRotateRight(k3->left);
		singleRotateLeft(k3);
	}
	
	//Double rotation with right child
	void doubleRotateRight(AVLNode * & k3)
	{
		singleRotateLeft(k3->right);
		singleRotateRight(k3);
	}
	
	//Insert x into the AVL tree
	void insert(int x)
	{
		insert(x, root);
	}
	
	//Recursive function to insert x into the AVL tree
	void insert(int &x, AVLNode * & n)
	{
		//If the node is null, place new element here
		if(n == NULL)
			n = new AVLNode(x, NULL, NULL);
		//If x is less than current item
		else if(x < n->element)
		{	
			//Insert x to the left node
			insert(x, n->left);
			if(height(n->left) - height(n->right) == 2)
			{
				if(x < (n->left)->element)
					singleRotateLeft(n);
				else
					doubleRotateLeft(n);
			}			
		}
		
		else if(x > n->element)
		{
			insert(x, n->right);
			if(height(n->right) - height(n->left) == 2)
			{
				if(x > (n->right)->element)
					singleRotateRight(n);
				else
					doubleRotateRight(n);
			}
		}
		else
			;
		
		//Update the height by adding 1 to node n's height
		n->height = max(height(n->left), height(n->right)) + 1;
	}
	
	//Finds x in the AVL tree
	bool access(int x)
	{
		return access(x, root);
	}
	
	//Recursive function to find x in the AVL tree
	//Returns true if element is in the AVL, returns false if it is not
	bool access(int x, AVLNode *n)
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
	
	//Removes x in the AVL tree
	void remove(int x)
	{
		remove(x, root);
	}
	
	//Gets the difference of heights between the left child and right child of node n
	int getBalance(AVLNode *n)
	{
		if(n == NULL)
			return 0;
		return height(n->left) - height(n->right);
	}
	
	//Recursive function to remove x in the AVL tree
	void remove(int x, AVLNode *&n)
	{
		//Original BST remove
		if(n == NULL)
			return;
		//Progress through the tree
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
			AVLNode *temp = n;
			if(n->left != NULL)
				n = n->left;
			else
				n = n->right;
		}
		
		if(n == NULL)
			return;
		
		
		//Rebalance the tree after removing
		n->height = max(height(n->left), height(n->right)) + 1;
		int nBalance = height(n->left) - height(n->right);
		int leftBalance = getBalance(n->left);
		int rightBalance = getBalance(n->right);
		
		if(nBalance > 1 && leftBalance >=0)
		{
			singleRotateLeft(n);
		}
		if(nBalance > 1 && leftBalance < 0)
		{
			doubleRotateLeft(n);
		}
		if(nBalance < -1 && rightBalance <= 0)
		{
			singleRotateRight(n);
		}
		if(nBalance < -1 && rightBalance > 0)
		{
			doubleRotateRight(n);
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
	void printTreeInOrder (AVLNode *n, ostream & out)
	{
		if(n != NULL)
		{
			printTreeInOrder(n->left, out);
			out << n-> element << " ";
			printTreeInOrder(n->right, out);
		}			
	}
	
	//Recursive function to print subtree rooted at n in pre order
	void printTreePreOrder (AVLNode *n, ostream & out)
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
	AVL *a = new AVL();
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
			if((a->access(val)) == true)
				cout << "Element already inserted" << endl;
			else
			{
				a->insert(val);
				cout << "Element inserted" << endl;
			}
		}
		
		if(str.compare("access") == 0)
		{
			cin >> val;
			if((a->access(val)) == true)
				cout << "Element accessed" << endl;
			else
				cout << "Element not found" << endl;
		}
		
		if(str.compare("delete") == 0)
		{
			cin >> val;
			a->remove(val);
		}
		
		if(str.compare("print") == 0)
		{
			a->printTree();
		}		
		
		cin >> str;		
	}	
	end = clock();
	cout << "time took: " << (float(end-start)/(CLOCKS_PER_SEC/1000)) << endl;
	return 0;
}


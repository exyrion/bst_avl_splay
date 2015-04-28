//Justin Liang
//CS130a
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>

using namespace std;

class SplayNode
{
	public:
	int element;
	SplayNode *left;
	SplayNode *right;
	
	SplayNode()
	{
		left = NULL;
		right = NULL;
	}
	SplayNode(int x, SplayNode *lt, SplayNode *rt)
	{
		element = x;
		left = lt;
		right = rt;
	}
};

class Splay
{
	private:
	SplayNode *root;
	SplayNode *nullNode;
	
	public:
	Splay()
	{
		nullNode = new SplayNode();
		nullNode->left = nullNode->right = nullNode;
		nullNode->element = 0;
		root = nullNode;
		
	}
		
	//Single rotation with left child
	void singleRotateLeft(SplayNode * & k2)
	{
		SplayNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2 = k1;		
	}
	
	//Single rotation with right child
	void singleRotateRight(SplayNode * & k1)
	{
		SplayNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1 = k2;		
	}test
	
	//Splay
	void splay(int &x, SplayNode *& n)
	{
		//Create local variables to store temporary values for splaying
		SplayNode *leftMax, *rightMin;
		static SplayNode temp;
		temp.left = temp.right = nullNode;
		leftMax = rightMin = &temp;
		
		nullNode->element = x;
		
		//Enter loop until element is splayed to the top (root)
		for( ; ; )
		{
			//If x is less than the current node's element, perform a single rotate
			//with left child
			if(x < n->element)
			{
				if(x < n->left->element)
					singleRotateLeft(n);
				if(n->left == nullNode)
					break;
				rightMin->left = n;
				rightMin = n;
				n = n->left;
			}
			
			//If x is less than the current node's element, perform a single rotate
			//with right child
			else if(x > n->element)
			{
				if(x > n->right->element)
					singleRotateRight(n);
				if(n->right == nullNode)
					break;
				leftMax->right = n;
				leftMax = n;
				n = n->right;
			}
			else
				break;
		}
		
		//Relink nodes
		leftMax->right = n->left;
		rightMin->left = n->right;
		n->left = temp.right;
		n->right = temp.left;
				
	}
	//Insert x into the Splay tree
	void insert(int &x)
	{
		static SplayNode *temp = NULL;
		
		if(temp == NULL)
			temp = new SplayNode;
			
		temp->element = x;
		
		if(root == nullNode)
		{
			temp->left = temp->right = nullNode;
			root = temp;
		}
		
		else
		{
			splay(x, root);
			if(x < root->element)
			{
				temp->left = root->left;
				temp->right = root;
				root->left = nullNode;
				root = temp;
			}
			else
			if(x > root->element)
			{
				temp->right = root->right;
				temp->left = root;
				root->right = nullNode;
				root = temp;
			}
			else
				return;		
		}
		temp = NULL;
	}
	
	//Finds x in the Splay tree
	bool access(int x)
	{
		if(root == nullNode)
			return false;
		splay(x, root);
		if(root->element != x)
			return false;
		return true;
	}
	
	//Removes x in the Splay tree
	void remove(int x)
	{
		SplayNode *temp;
		splay(x, root);
		if(root->element != x)
			return;
		if(root->left == nullNode)
			temp = root->right;
		else
		{
			temp = root->left;
			splay(x, temp);
			temp->right = root->right;
		}
		delete root;
		root = temp;			
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
	void printTreeInOrder (SplayNode *n, ostream & out)
	{
		if(n != nullNode)
		{
			printTreeInOrder(n->left, out);
			out << n-> element << " ";
			printTreeInOrder(n->right, out);
		}			
	}
	
	//Recursive function to print subtree rooted at n in pre order
	void printTreePreOrder (SplayNode *n, ostream & out)
	{
		if(n != nullNode)
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
	Splay *s = new Splay();
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
			
			if((s->access(val)) == true)
				cout << "Element already inserted" << endl;
			else
			{
				s->insert(val);
				cout << "Element inserted" << endl;
			}
		}
		
		if(str.compare("access") == 0)
		{
			cin >> val;
			if((s->access(val)) == true)
				cout << "Element accessed" << endl;
			else
				cout << "Element not found" << endl;
		}
		
		if(str.compare("delete") == 0)
		{
			cin >> val;
			s->remove(val);
		}
		
		if(str.compare("print") == 0)
		{
			s->printTree();
		}		
		
		cin >> str;		
	}
	
	end = clock();
	cout << "time took: " << (float(end-start)/(CLOCKS_PER_SEC/1000)) << endl;
	return 0;
}


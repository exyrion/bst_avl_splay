//Justin Liang
//CS130A
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

int main()
{
	//Insert 10000 integers to file1.txt in increasing order, access them, 
	//and delete them in the same order
	ofstream file1;
	file1.open("file1");
	
	for(int i = 0; i < 10000; i++)
	{
		file1 << "insert " << i << endl;
	}	
	for(int i = 0; i < 10000; i++)
	{
		file1 << "access " << i << endl;
	}	
	for(int i = 0; i < 10000; i++)
	{
		file1 << "delete " << i << endl;
	}
	file1.close();
	
	
	//Insert 10000 integers to file2.txt in increasing order 
	//and delete them in reverse order
	ofstream file2;
	file2.open("file2");
	
	for(int i = 0; i < 10000; i++)
	{
		file2 << "insert " << i << endl;
	}	
	for(int i = 10000; i > 0; i--)
	{
		file2 << "delete " << i << endl;
	}
	file2.close();
	
	
	//Insert 10000 integers to file3.txt in random order 
	//and delete them in random order	
	ofstream file3;
	file3.open("file3");	
	int array[10000];
	for(int i = 0; i < 10000; i++)
	{
		array[i] = i;
	}
	random_shuffle(array, array+10000); //Shuffles the contents of array
	
	for(int i = 0; i < 10000; i++)
	{
		file3 << "insert " << array[i] << endl;
	}
	
	random_shuffle(array, array+10000); //Shuffles the contents of the array again
	for(int i = 0; i < 10000; i++)
	{
		file3 << "delete " << array[i] << endl;
	}
	file3.close();
	return 0; 
}


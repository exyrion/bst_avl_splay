all: bst avl splay tree_testing

bst: bst.o
	g++ bst.o -o bst
bst.o: bst.cpp
	g++ bst.cpp -c
avl: avl.o
	g++ avl.o -o avl
avl.o: avl.cpp
	g++ avl.cpp -c
splay: splay.o
	g++ splay.o -o splay
splay.o: splay.cpp
	g++ splay.cpp -c
tree_testing: tree_testing.o
	g++ tree_testing.o -o tree_testing
tree_testing.o: tree_testing.cpp
	g++ tree_testing.cpp -c

segTree: main.o segtree.o
	clang++ -o segTree segtree.o main.o

main.o: main.cpp 
	clang++ -std=c++14 -c main.cpp 

segtree.o: segtree.cpp segtree.h 
	clang++ -std=c++14 -c segtree.cpp

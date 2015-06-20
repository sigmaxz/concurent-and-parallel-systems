all:ex1arr.cpp ex1reg.cpp ex2.cpp matmul.c ex4.cpp
	g++ -fopenmp ex1arr.cpp -o ex1arr
	g++ -fopenmp ex1reg.cpp -o ex1reg	
	g++ -fopenmp ex2.cpp -o ex2
	g++ -fopenmp matmul.c -o matmul
	g++ -fopenmp ex4.cpp -o ex4
	g++ -fopenmp ex5.cpp -o ex5
	g++ -fopenmp ex6.cpp -o ex6

ex1arr: ex1arr.cpp
	g++ -fopenmp ex1arr.cpp -o ex1arr

ex1reg: ex1reg.cpp
	g++ -fopenmp ex1reg.cpp -o ex1reg
	
ex2: ex2.cpp
	g++ -fopenmp ex2.cpp -o ex2
matmul: matmul.c
	g++ -fopenmp matmul.c -o matmul
ex4: ex4.cpp
	g++ -fopenmp ex4.cpp -o ex4
	
ex5: ex5.cpp
	g++ -fopenmp ex5.cpp -o ex5
clean:
	rm ex1arr ex1reg ex2 matmul ex4 ex5 ex6

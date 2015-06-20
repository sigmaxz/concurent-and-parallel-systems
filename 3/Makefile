all:	matrix.cpp mt.cpp
	g++ -lpthread matrix.cpp -o matrix
	g++ -lpthread mt.cpp -o mt
	g++ -lpthread mt2.cpp -o mt2

matrix: matrix.cpp
	g++ -lpthread matrix.cpp -o matrix
	
mt:	mt.cpp
	g++ -lpthread mt.cpp -o mt
	
mt2: mt2.cpp
	g++ -lpthread mt2.cpp -o mt2

ex1: ex1.cpp
	g++ -lpthread ex1.cpp -o ex1

ex2: ex2.cpp
	g++ -lpthread ex2.cpp -o ex2
	
ex3: ex3.cpp
	g++ -lpthread ex3.cpp -o ex3

test1: ex1
	ex1
	
test2: ex2
	ex2
	
test3: ex3
	ex3
test: mt2 matrix
	echo Timing matrix
	(time matrix) 1> out1.txt
	echo Timing mt2
	(time mt2) 1> out2.txt
	echo doing diff on two files
	diff out1.txt out2.txt
	echo done if nothing identical
	echo test done
	
clean:
	rm matrix mt mt2 out1.txt out2.txt ex1 ex2 ex3

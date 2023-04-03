all:
	g++ main.cpp -L../../build/ -lflixel++ -I. -I../../include/ -O3 -o example
run:
	LD_LIBRARY_PATH="../../build/" ./example 
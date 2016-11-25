.DEFAULT_GOAL := build

build:
	g++ main.cpp -l curl -fopenmp -std=c++11

clean:
	rm -rf output a.out

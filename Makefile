.DEFAULT_GOAL := build

build:
	g++ main.cpp -l curl -fopenmp

clean:
	rm -rf output a.out

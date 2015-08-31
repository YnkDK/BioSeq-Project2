BIN = bin
ALIGNMENT = global_linear.cpp
#UTILS = input_reader.cpp performance.cpp
FLAGS = -O3 -Wall -std=c++0x -march=native

main: *.cpp *.h
	mkdir -p $(BIN)
	mkdir -p output
	g++ $(FLAGS) $(UTILS) $(ALIGNMENT) main.cpp -o $(BIN)/main
#	g++ $(FLAGS) testcaseGenerator.cpp -o $(BIN)/generator
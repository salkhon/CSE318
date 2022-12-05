main.out: main.cpp ./Board/Board.hpp ./Board/Board.cpp ./Board/BoardFactory/BoardFactory.hpp ./Board/BoardFactory/BoardFactory.cpp ./Solver/Solver.hpp ./Solver/Solver.cpp
	g++ -std=c++20 main.cpp ./Board/Board.cpp ./Board/BoardFactory/BoardFactory.cpp ./Solver/Solver.cpp -o main.out

clean:
	rm *.out *.o
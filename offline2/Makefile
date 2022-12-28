main: main.cpp ./CSPSolver/CSPSolver.cpp ./ConstraintGraph/ConstraintGraph.cpp ./VariableOrderHeuristic/VariableOrderHeuristic.cpp ./VariableOrderHeuristic/SmallestDomain/SmallestDomainHeuristic.cpp ./VariableOrderHeuristic/SmallestDomainMaxDegree/SmallestDomainMaxDegreeHeuristic.cpp ./VariableOrderHeuristic/Random/RandomHeuristic.cpp ./VariableOrderHeuristic/MaxDegree/MaxDegreeHeuristic.cpp ./VariableOrderHeuristic/DomainSizeByDegree/DomainSizeByDegreeHeuristic.cpp ./Variable/Variable.cpp
	g++ main.cpp ./Variable/Variable.cpp \
	./ConstraintGraph/ConstraintGraph.cpp \
	./VariableOrderHeuristic/VariableOrderHeuristic.cpp \
	./VariableOrderHeuristic/SmallestDomain/SmallestDomainHeuristic.cpp \
	./VariableOrderHeuristic/SmallestDomainMaxDegree/SmallestDomainMaxDegreeHeuristic.cpp \
	./VariableOrderHeuristic/Random/RandomHeuristic.cpp \
	./VariableOrderHeuristic/MaxDegree/MaxDegreeHeuristic.cpp \
	./VariableOrderHeuristic/DomainSizeByDegree/DomainSizeByDegreeHeuristic.cpp \
	./CSPSolver/CSPSolver.cpp \
	-o main.out

clean:
	rm *.out *.o	
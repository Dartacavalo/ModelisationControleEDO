progs = main.out
flags = -Wall

all: $(progs)

main.out: main.cpp Solver.o CasTest.o
	g++ -o $@ $^ $(flags)

CasTest.o: CasTest.cpp Solver.hpp PbCauchy.hpp
	g++ -c $< $(flags)

Solver.o: Solver.cpp Solver.hpp PbCauchy.hpp
	g++ -c $< $(flags)

clean:
	rm *.o *.txt *.bat $(progs)

progs = main.out
flags =

all: $(progs)

main.out: main.cpp PbCauchy.o Solver.o CasTest.o
	g++ -o $@ $^ $(flags)

CasTest.o: CasTest.cpp Solver.hpp PbCauchy.hpp
	g++ -c $^ $(flags)

Solver.o: Solver.cpp Solver.hpp 
	g++ -c $< $(flags)

PbCauchy.o: PbCauchy.cpp PbCauchy.hpp
	g++ -c $< $(flags)

clean:
	rm *.o *.txt *.gch $(progs)

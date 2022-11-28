progs = test_essay1
flags =

all: $(progs)

test_essay1: main.cpp PbCauchy.o Solver.o CasTest.o
	g++ -o $@ $^ $(flags)

CasTest.o: CasTest.cpp Solver.hpp PbCauchy.hpp
	g++ -c $^ $(flags)

Solver.o: Solver.cpp Solver.hpp 
	g++ -c $< $(flags)

PbCauchy.o: PbCauchy.cpp PbCauchy.hpp
	g++ -c $< $(flags)

clean:
	rm *.o  $(progs)

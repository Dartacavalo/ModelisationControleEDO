progs = main.out
flags =

all: $(progs)

main.out: main.cpp Solver.o CasTest.o PbCauchy.hpp
	g++ -o $@ $^ $(flags)

CasTest.o: CasTest.cpp Solver.hpp PbCauchy.hpp
	g++ -c $< $(flags)

Solver.o: Solver.cpp Solver.hpp PbCauchy.hpp
	g++ -c $< $(flags)

clean:
	rm *.o *.txt $(progs)

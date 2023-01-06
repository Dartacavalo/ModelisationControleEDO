CC = g++
PROGS = main tests
FLAGS = -Wall
SRC = code/
EXEC = exec/
COMPILED = objets/
OBJETS = *.o
SORTIES = *.txt *.bat

all: $(PROGS)

main: main.cpp FonctionsTest.o Controle.o Integrale.o Schema.o
	$(CC) -o $@ $(COMPILED)$^ $(FLAGS)

tests: mainTests.cpp $(OBJETS)
	$(CC) -o $@ $(COMPILED)$^ $(FLAGS)

FonctionsTest.o: FonctionsTest.cpp FonctionsTest.hpp
	$(CC) -c $(SRC)$< $(FLAGS)

Controle.o: Controle.cpp Integrale.hpp PbCauchy.hpp
	$(CC) -c $(SRC)$< $(FLAGS)

Integrale.o: Integrale.cpp Integrale.hpp
	$(CC) -c $(SRC)$< $(FLAGS)

CasTest.o: CasTest.cpp Schema.hpp PbCauchy.hpp
	$(CC) -c $(SRC)$< $(FLAGS)

Schema.o: Schema.cpp Schema.hpp PbCauchy.hpp
	$(CC) -c $(SRC)$< $(FLAGS)

clean:
	rm -f $(OBJETS) $(SORTIES) $(PROGS)

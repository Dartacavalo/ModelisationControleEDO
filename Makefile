CC = g++
PROGS = main tests
FLAGS = -Wall
SRC = code
GNUPLOT = gnuplot_files
DATA = data

all: $(PROGS)

main: $(SRC)/main.cpp $(SRC)/FonctionsTest.o $(SRC)/Controle.o $(SRC)/Integrale.o $(SRC)/Schema.o
	$(CC) -o $@ $^ $(FLAGS)

tests: $(SRC)/mainTests.cpp $(SRC)/FonctionsTest.o $(SRC)/Controle.o $(SRC)/Integrale.o $(SRC)/Schema.o $(SRC)/CasTest.o
	$(CC) -o $@ $^ $(FLAGS)

$(SRC)/FonctionsTest.o: $(SRC)/FonctionsTest.cpp $(SRC)/FonctionsTest.hpp
	$(CC) -c $< $(FLAGS) -o $@

$(SRC)/Controle.o: $(SRC)/Controle.cpp $(SRC)/Integrale.hpp $(SRC)/PbCauchy.hpp
	$(CC) -c $< $(FLAGS) -o $@

$(SRC)/Integrale.o: $(SRC)/Integrale.cpp $(SRC)/Integrale.hpp
	$(CC) -c $< $(FLAGS) -o $@

$(SRC)/CasTest.o: $(SRC)/CasTest.cpp $(SRC)/Schema.hpp $(SRC)/PbCauchy.hpp
	$(CC) -c $< $(FLAGS) -o $@

$(SRC)/Schema.o: $(SRC)/Schema.cpp $(SRC)/Schema.hpp $(SRC)/PbCauchy.hpp
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm -f $(PROGS) $(SRC)/*.o $(DATA)/*.txt $(GNUPLOT)/*.bat

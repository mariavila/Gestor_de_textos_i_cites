CXXFLAGS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe:Taula.o Frase.o program.o Text.o Biblioteca.o
	g++ -o program.exe program.o Text.o Frase.o Biblioteca.o Taula.o

program.o: program.cc
	g++ $(CXXFLAGS) -c program.cc

Taula.o: Taula.cc
	g++ $(CXXFLAGS) -c Taula.cc

Frase.o: Frase.cc
	g++ $(CXXFLAGS) -c Frase.cc
	
Text.o: Text.cc
	g++ $(CXXFLAGS) -c Text.cc

Biblioteca.o: Biblioteca.cc
	g++ $(CXXFLAGS) -c Biblioteca.cc

clean:
	rm -f *.o

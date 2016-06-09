CXXFLAGS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe:Taula.o Frase.o program.o Text.o Biblioteca.o
	g++ -o program.exe program.o Text.o Frase.o Biblioteca.o Taula.o

%.o: %.cc
	g++ $(CXXFLAGS) -c $^ -o $@

clean:
	rm -f *.o

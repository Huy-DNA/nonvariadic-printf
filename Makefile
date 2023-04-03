SHELL       := /bin/bash
CXX         := g++
PRINTFDIR   := my-printf-source/
CXXFLAGS    := -I $(PRINTFDIR)

.PHONY      := test clean

main: my_printf.o main.cpp pre-preprocessor.py
	@ python3 pre-preprocessor.py main.cpp
	@ $(CXX) $(CXXFLAGS) -o main main.output.cpp my_printf.o

test: my_printf.o $(PRINTFDIR)/test.cpp $(PRINTFDIR)/my_printf.h
	@ $(CXX) $(CXXFLAGS) -o main $(PRINTFDIR)/test.cpp my_printf.o

my_printf.o: $(PRINTFDIR)/my_printf.cpp $(PRINTFDIR)/my_printf.h
	@ $(CXX) $(CXXFLAGS) -o my_printf.o -c $(PRINTFDIR)/my_printf.cpp

clean:
	rm -rf *.o main *.output.cpp

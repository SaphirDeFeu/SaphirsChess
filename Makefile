CXX = g++
CXXFLAGS = -Wall -Werror -I../include

main: src/main.cpp
	cd build && $(CXX) $(CXXFLAGS) ../src/main.cpp -c
	cd build && $(CXX) $(CXXFLAGS) main.o -o saphirschess

run:
	make
	./build/saphirschess.exe
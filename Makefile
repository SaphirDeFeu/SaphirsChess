CXX = g++
CXXFLAGS = -Wall -Werror -I../include

main: src/main.cpp src/piece.cpp src/state.cpp
	cd build && $(CXX) $(CXXFLAGS) ../src/main.cpp -c
	cd build && $(CXX) $(CXXFLAGS) ../src/piece.cpp -c
	cd build && $(CXX) $(CXXFLAGS) ../src/state.cpp -c
	cd build && $(CXX) $(CXXFLAGS) ../src/board.cpp -c
	cd build && $(CXX) $(CXXFLAGS) main.o piece.o state.o board.o -o saphirschess

run:
	make
	./build/saphirschess.exe
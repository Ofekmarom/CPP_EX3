#ID : 208336701
#mail : ofekmarom9@gmail.com

#matala 3

CXX = clang++
CXXFLAGS = -std=c++11 -Werror -g -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# Source files
SRC_DEMO = Demo.cpp Board.cpp Catan.cpp DevelopmentCard.cpp Edge.cpp Hexagon.cpp Player.cpp Vertex.cpp
SRC_TEST = Test.cpp Board.cpp Catan.cpp DevelopmentCard.cpp Edge.cpp Hexagon.cpp Player.cpp Vertex.cpp

# Object files
OBJ_DEMO = $(SRC_DEMO:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

# Targets
all: demo test

catan: demo
	./$^
runtest: test
	./$^

demo: $(OBJ_DEMO)
	$(CXX) $(CXXFLAGS) $(OBJ_DEMO) -o demo

test: $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) $(OBJ_TEST) -o test


valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test
CXX=g++
LDFLAGS=$$(fltk-config --ldflags)

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXE=text-editor

all: $(OBJ) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CXX) -c $< -o $@

clean:
	rm -rf *.o $(EXE)
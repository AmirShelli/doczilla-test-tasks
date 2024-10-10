appname := concat

CXX := clang++
CXXFLAGS := -std=c++17 -Iinc

SRCDIR := src
INCDIR := inc
TESTDIR := test

srcfiles := $(wildcard $(SRCDIR)/*.cpp)
objects  := $(srcfiles:.cpp=.o)

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) -o $(appname) $(objects)
	@rm -f $(objects) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(appname) $(SRCDIR)/*.o

run: $(appname)
	./$(appname) $(if $(arg),$(arg),$(TESTDIR))

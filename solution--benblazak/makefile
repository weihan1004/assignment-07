# -----------------------------------------------------------------------------
# Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
# Released under the [MIT License] (http://opensource.org/licenses/MIT)
# -----------------------------------------------------------------------------

TARGET := main

SRC := $(wildcard *.cpp)

CXX := clang++
CXXFLAGS := -std=c++11

# -----------------------------------------------------------------------------
.PHONY: all clean cleanall run

all: $(TARGET)

clean:
	-rm $(TARGET)

cleanall: clean

run: all
	./$(TARGET)

# -----------------------------------------------------------------------------

$(TARGET): $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

# -----------------------------------------------------------------------------
# .PHONY: new-input
# 
# new-input:
# 	od -An -t d1 -N100 /dev/random  | perl -p -e 's/\s*([+-]?[\d.]+(e[+-]\d+)?)\s*/\1\n/g' > input-int-1.txt
# 	od -An -t d1 -N200 /dev/random  | perl -p -e 's/\s*([+-]?[\d.]+(e[+-]\d+)?)\s*/\1\n/g' > input-int-2.txt
# 	od -An -t f4 -N800 /dev/random  | perl -p -e 's/\s*([+-]?[\d.]+(e[+-]\d+)?)\s*/\1\n/g' > input-double-2.txt
# 	od -An -t f4 -N1200 /dev/random | perl -p -e 's/\s*([+-]?[\d.]+(e[+-]\d+)?)\s*/\1\n/g' > input-double-3.txt
# 	od -An -t d1 -N500 /dev/random  | perl -p -e 's/\s*([+-]?[\d.]+(e[+-]\d+)?)\s*/\1\n/g' > input-int-5.txt
# 	od -An -t d1 -N300 /dev/random  | perl -p -e 's/\s*([+-]?[\d.]+(e[+-]\d+)?)\s*/\1\n/g' > input-int-3-bad.txt


CXX = g++
CXXFLAGS = -g -Wall -std=c++17

OFILES = wordcounts.o


TARGET = wordcounts

all:		$(TARGET)

$(TARGET):	$(OFILES)
		$(CXX) $(OFILES) -o $@
clean:
	rm -f *.o

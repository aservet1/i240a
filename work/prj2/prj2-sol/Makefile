CXX = g++
CXXFLAGS = -g -Wall -std=c++17

FILES_TO_COMPILE = arrayseq.hh seq.hh nums.cc


TARGET = seq-test

all:		$(TARGET)

$(TARGET):	$(FILES_TO_COMPILE)
		$(CXX) $(CXXFLAGS) $(FILES_TO_COMPILE) -o $@
clean:
	rm -f *.o $(TARGET)

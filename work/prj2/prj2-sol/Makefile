CXX = g++
CXXFLAGS = -g -Wall -std=c++17

NUMS_FILES = nums.cc
SEQ_TEST_FILES = command.cc seq-test.cc


NUMS_TARGET = nums
SEQ_TEST_TARGET = seq-test

all:		$(NUMS_TARGET) $(SEQ_TEST_TARGET)

$(NUMS_TARGET):	$(NUMS_FILES)
		$(CXX) $(CXXFLAGS) $(NUMS_FILES) -o $@

$(SEQ_TEST_TARGET): $(SEQ_TEST_FILES)

clean:
	rm -f *.o $(NUMS_TARGET) $(SEQ_TEST_TARGET)

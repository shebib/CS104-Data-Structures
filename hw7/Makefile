CC       = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR) iteratorTest avlTest sat_solver

iteratorTest: iteratorTest.cpp 
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

avlTest: avlTest.cpp
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

sat_solver: sat_solver.cpp
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

.PHONY: clean

clean:
	rm iteratorTest avlTest sat_solver
	-@echo "--- All Clean!---" 

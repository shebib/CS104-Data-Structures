CC       = g++
CPPFLAGS = -Wall -g -std=c++11

all: $(BIN_DIR) avlTest sat_solver

avlTest: avlTest.cpp avlbst.h
	$(CC) $(CPPFLAGS) $^ -o $@

sat_solver: sat_solver.cpp
	$(CC) $(CPPFLAGS) $^  -o $@

.PHONY: clean

clean:
	rm avlTest sat_solver
	-@echo "--- All Clean!---" 

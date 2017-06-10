## Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
# .o files will be stored here
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR) copytest settest majors

$(BIN_DIR): 
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
copytest: copytest.cpp $(BIN_DIR)/lliststr.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/lliststr.o: $(BIN_DIR) lliststr.cpp 
	$(CC) $(CPPFLAGS) lliststr.cpp -c -o $@
	
settest: $(BIN_DIR)/lliststr.o settest.cpp $(BIN_DIR)/setstr.o 
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/setstr.o: setstr.cpp
	$(CC) $(CPPFLAGS) $^ -c -o $@

majors: $(BIN_DIR)/lliststr.o majors.cpp $(BIN_DIR)/setstr.o 
	$(CC) $(CPPFLAGS) $^ -o $@

.PHONY: tests clean

clean:
	rm -rf $(BIN_DIR)
	rm copytest settest majors
	
	-@echo "--- All Clean!---" 

CC       = g++
CPPFLAGS = -Wall -g
# .o files will be stored here
BIN_DIR  = bin

all: $(BIN_DIR) twitter

$(BIN_DIR): 
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

twitter: twitter.cpp $(BIN_DIR)/datetime.o $(BIN_DIR)/tweet.o $(BIN_DIR)/twiteng.o $(BIN_DIR)/user.o 
	$(CC) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/datetime.o: $(BIN_DIR) datetime.cpp 
	$(CC) $(CPPFLAGS) datetime.cpp -c -o $@

$(BIN_DIR)/tweet.o: $(BIN_DIR) tweet.cpp 
	$(CC) $(CPPFLAGS) tweet.cpp -c -o $@

$(BIN_DIR)/twiteng.o: $(BIN_DIR) twiteng.cpp 
	$(CC) $(CPPFLAGS) twiteng.cpp -c -o $@

$(BIN_DIR)/user.o: $(BIN_DIR) user.cpp 
	$(CC) $(CPPFLAGS) user.cpp -c -o $@

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)
	rm twitter
	rm *.feed
	
	-@echo "--- All Clean!---"

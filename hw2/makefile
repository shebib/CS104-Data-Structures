remdup: remdup.cpp
	g++ -g -Wall remdup.cpp -o ./remdup

llistint.o: llistint.cpp
	g++ -g -c -Wall llistint.cpp -o ./llistint.o

testAddToEmptyList: testAddtoEmptyList.cpp llistint.o
	g++ -g -Wall llistint.o testAddToEmptyList.cpp -o ./testAddToEmptyList

alistint.o: alistint.cpp
	g++ -g -c -Wall alistint.cpp -o ./alistint.o

testAList: alistint.o testAList.cpp
	g++ -g -Wall alistint.o testAList.cpp -o ./testAList

stackint.o: stackint.cpp
	g++ -g -c -Wall stackint.cpp -o ./stackint.o

laundry: laundry.cpp stackint.o llistint.o
	g++ -g -Wall stackint.o llistint.o laundry.cpp -o ./laundry

clean:
	rm ./remdup ./llistint.o ./testAddToEmptyList ./testAList ./alistint.o ./stackint.o ./laundry

# All Targets

all: hello

hello: bin/main.o bin/Order.o bin/Volunteer.o bin/Customer.o bin/WareHouse.o bin/Action.o #Link
	g++ -o bin/warehouse bin/main.o bin/Order.o bin/Volunteer.o bin/Customer.o bin/WareHouse.o bin/Action.o

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Order.o: src/Order.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Order.o src/Order.cpp

bin/Volunteer.o: src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Volunteer.o src/Volunteer.cpp

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp

bin/WareHouse.o: src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/WareHouse.o src/WareHouse.cpp

bin/Action.o: src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp

clean:
	rm -f bin/*
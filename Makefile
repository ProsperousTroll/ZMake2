make:
	g++ -I./inc ./src/main.cpp -o zmake

clean: 
	rm ./zmake

build:
	rm ./zmake
	g++ -I./inc ./src/main.cpp -o zmake

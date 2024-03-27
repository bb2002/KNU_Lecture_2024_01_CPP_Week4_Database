FLAGS = -Werror -std=c++11

main.exe: main.o database.o parser.o
	g++ -o main.exe main.o database.o parser.o

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

database.o: database.cpp
	g++ ${FLAGS} -c database.cpp

parser.o: parser.cpp
	g++ ${FLAGS} -c parser.cpp

clean:
	rm *.o
	rm main
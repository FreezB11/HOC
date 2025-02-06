CC = g++ -std=c++20
OUT = HOC
FILES =  src/*.c++ lib/*.h

all:
	${CC} -o ${OUT} main.cc ${FILES} 

client:
	${CC} -o client client.cc ${FILES}
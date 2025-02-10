CC = g++ -std=c++20
OUT = build/HOC
FILES =  src/*.cc# lib/*.cc

all:
	${CC} -o ${OUT} main.cc ${FILES} 

client:
	${CC} -o build/client client.cc ${FILES}
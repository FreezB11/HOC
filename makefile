CC = g++
OUT = HOC
FILES = main.cc src/*.c++

all:
	${cc} -o ${OUT} ${FILES} 
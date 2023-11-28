all: clean compile run
compile: main.cpp
	@g++ -o main main.cpp board.cpp pieces.cpp
run:
	@./main
clean:
	@rm -f *.o


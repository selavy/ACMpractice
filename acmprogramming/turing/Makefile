all: build
	./turing input.txt > test_output.txt
	diff test_output.txt output.txt
build:
	gcc -Wall -Werror -g main.c -o turing
clean:
	rm -f turing test_output* *~

all: build
	./caesaris input.txt > test_output.txt
	diff test_output.txt output.txt
build:
	gcc -Wall -g main.c -o caesaris
clean:
	rm test_output.txt caesaris

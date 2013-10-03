all: build
	./cube input.txt > test_output.txt
	diff output.txt test_output.txt
test: build
	./cube input.txt
build:
	gcc -g -Wall -Werror main.c -o cube
clean:
	rm -f cube test_output.txt *~

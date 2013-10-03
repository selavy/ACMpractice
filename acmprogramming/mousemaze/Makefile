all: build
	./maze input.txt > test_output.txt
	diff test_output.txt output.txt
build:
	gcc -g -Wall -Werror main.c -o maze
clean:
	rm -f test_output* maze

all: build
	./goodevil input.txt > test_output.txt
	diff test_output.txt output.txt
test: build
	./goodevil input.txt
build:
	gcc -g -Wall -Werror main.c -o goodevil
clean:
	rm -f goodevil test_output.txt *~

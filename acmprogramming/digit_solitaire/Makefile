all: build
	./solitaire digits.in > test_output.txt
	diff test_output.txt output.txt
build:
	gcc -g -Wall -Werror main.c -o solitaire
clean:
	rm -f solitaire test_output* *~

all: build
	./multiple input.txt > test_output.txt
	diff test_output.txt output.txt
test: build
	./multiple input.txt
build:
	gcc -Wall -Werror -g main.c -o multiple
clean:
	rm -f multiple test_output.* *~

all: build
	./smart input.txt > test_output.txt
	cat test_output.txt
build:
	gcc -Wall -Werror -g main.c -o smart
clean:
	rm -f smart test_output* *~

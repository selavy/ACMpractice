all: build
	./complex input.txt > test_output.txt
	diff test_output.txt output.txt
build:
	gcc -Wall -Werror -g main.c -o complex
clean:
	rm -f complex test_output* *~

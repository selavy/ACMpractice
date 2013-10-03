all: build
	./administrator input1.txt > test_output1.txt
	./administrator input2.txt > test_output2.txt
	./administrator input3.txt > test_output3.txt
	diff test_output1.txt output1.txt
	diff test_output2.txt output2.txt
	cat log.txt
build:
	gcc -Wall -g main.c -o administrator
clean-test:
	rm -f test*.txt
clean-inputs:
	rm -f input[!1-2]*
clean:
	rm -f administrator test*.txt log.txt

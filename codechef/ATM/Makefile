all: build
	./atm input1.txt > test_output1.txt
	./atm input2.txt > test_output2.txt
	./atm input3.txt > test_output3.txt
	diff output1.txt test_output1.txt
	diff output2.txt test_output2.txt
	diff output3.txt test_output3.txt
build:
	gcc -g -Wall -Werror main.c -o atm
clean:
	rm -rf test_output*.txt atm *~

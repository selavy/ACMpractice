all: test
test: main
	./hackman input1.txt > test_output1.txt
	./hackman input2.txt > test_output2.txt
	./hackman input3.txt > test_output3.txt
	diff output1.txt test_output1.txt
	diff output2.txt test_output2.txt
	diff output3.txt test_output3.txt
main:
	gcc -Wall main.c -g -o hackman
clean:
	rm -rf *.o hackman test_output*.txt *~

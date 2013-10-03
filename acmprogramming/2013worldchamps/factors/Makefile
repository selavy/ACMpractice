all: build
	./factors ../icpc2013-data/factors/sample/factors-001.in > test_output.txt
	diff test_output.txt ../icpc2013-data/factors/sample/factors-001.ans
test: build
	./factors ../icpc2013-data/factors/sample/factors-001.in
build:
	gcc -g -Wall -Werror main.c -o factors
clean:
	rm -f factors *~

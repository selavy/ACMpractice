use ./generate to create input files
./generate <number_of_books> <number_of_scribes>
./generate <number_of_books> <number_of_scribes> <output_file_name>

if no output_file_name is given, then it uses "input3.txt"

make will run the tests given in the problem set and diff the output to the output given.

log.txt records the time taken in seconds, not including i/o

make clean-inputs will delete all input files made with ./generate
make clean will delete all test output files and the executable
make clean-test will delete all test output files

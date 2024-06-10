CC=g++

all: bin/part0 bin/part1 bin/part2 bin/part3 bin/part4
clean:
	rm -f bin/part0
	rm -f bin/part1
	rm -f bin/part2
	rm -f bin/part3
	rm -f bin/part4

bin/part0: src/part0/part0.cc
	$(CC) -std=c++11 -o $@ src/part0/part0.cc

bin/part1: src/part1/part1.cc src/part1/part1.hh src/verif.hh src/shared.cc src/shared.hh src/params.hh
	$(CC) -std=c++11 -o $@ src/part1/part1.cc src/shared.cc bin/verif.o

bin/part2: src/part2/part2.cc src/part2/part2.hh src/verif.hh src/shared.cc src/shared.hh src/params.hh 
	$(CC) -std=c++11 -o $@ src/part2/part2.cc src/shared.cc bin/verif.o

bin/part3: src/part3/part3.cc src/util.hh src/verif.hh src/shared.cc src/shared.hh src/params.hh
	$(CC) -std=c++11 -o $@ src/part3/part3.cc src/util.hh src/shared.cc bin/verif.o

bin/part4: src/part4/part4.cc src/part4/part4.hh 
	$(CC) -std=c++11 -o $@ src/part4/part4.cc src/part4/gold



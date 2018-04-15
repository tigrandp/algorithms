EXEC = exec
OBJECTS = sorting.o input_generation.o

sorting: sorting.h sorting.cc Makefile
	g++ -g -c sorting.cc

input_generation: input_generation.cc input_generation.h Makefile
	g++ -g -c input_generation.cc

test: tester.cc input_generation sorting Makefile
	g++ -g $(OBJECTS) tester.cc -o exec

clean:
	rm $(OBJECTS) $(EXEC)

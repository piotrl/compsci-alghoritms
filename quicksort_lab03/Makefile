PROG = quicksort

FILES = testing.o quicksort.o
$(PROG) : $(FILES)
	gcc -Wall -std=c99 $(FILES) -o $(PROG).out -lrt -lm

testing.o : quicksort.h
quicksort_std.o : quicksort.h

clean :
	rm -f *~
	rm -f *.o
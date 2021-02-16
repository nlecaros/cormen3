sort : driver.o insertion_sort.o
	gcc -o sort driver.o insertion_sort.o

driver.o : driver.c algorithms.h
	gcc -c -g -O0 driver.c
insertion_sort.o : insertion_sort.c algorithms.h
	gcc -c -g -O0 insertion_sort.c 

clean : 
	rm -f sort driver.o insertion_sort.o

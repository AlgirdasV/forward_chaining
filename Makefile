OBJS = main.o algorithm.o
CC = gcc

isvedimas: $(OBJS)
	$(CC) $(OBJS) -o isvedimas -lstdc++
main.o: main.cpp 
	$(CC) -g -c main.cpp
algorithm.o: algorithm.cpp 
	$(CC) -g -c algorithm.cpp
clean:
	\rm *.o *~ kodavimas
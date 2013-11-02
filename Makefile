OBJS = main.o
CC = g++

isvedimas: $(OBJS)
	$(CC) $(OBJS) -o isvedimas
main.o: main.cpp
	$(CC) -g -c main.cpp
clean:
	\rm *.o *~ kodavimas
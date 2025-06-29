CC = gcc
CFLAGS = -Wall -O2 -g 

all: Debug/sort 

Debug/sort: Debug/Sorts.o Debug/Test.o Debug/MyRand.o Debug/Score.o Debug/SortString.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
Debug/%.o: %.c
	@mkdir -p Debug
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Debug/*.o Debug/sort 

run: Debug/sort
	cd Debug && ./sort > results.txt
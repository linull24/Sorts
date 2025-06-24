CC = gcc
CFLAGS_DEBUG = -Wall -g
CFLAGS_RELEASE = -Wall -O2 -DNDEBUG

all: debug release

debug: Debug/sorts

release: Release/sorts

Debug/sorts: Debug/Sorts.o Debug/Test.o Debug/MyRand.o Debug/Score.o Debug/SortString.o
	$(CC) $(CFLAGS_DEBUG) -o $@ $^ -lm

Release/sorts: Release/Sorts.o Release/Test.o Release/MyRand.o Release/Score.o Release/SortString.o
	$(CC) $(CFLAGS_RELEASE) -o $@ $^ -lm

Debug/%.o: %.c
	@mkdir -p Debug
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

Release/%.o: %.c
	@mkdir -p Release
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

clean:
	rm -f Debug/*.o Debug/sorts Release/*.o Release/sorts

run_debug: debug
	cd Debug && ./sorts > results.txt

run_release: release
	cd Release && ./sorts > results.txt
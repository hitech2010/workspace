OBJS = sansecEngine.o

all: sansecEngine.so sansecEngineTester
.PHONY: all

sansecEngine.so: $(OBJS)
	gcc -shared -o $@ $^ -lswsds
sansecEngine.o: sansecEngine.c
	gcc -c -fpic -o $@ $^

sansecEngineTester: sansecEngineTester.c
	gcc -o $@ $^ -lcrypto

.PHONY: clean
clean:
	rm -rf *.o sansecEngineTester sansecEngine.so
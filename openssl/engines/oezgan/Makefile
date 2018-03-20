OBJS = oezganEngine.o

all: oezganEngine.so oezganEngineTester
.PHONY: all

oezganEngine.so: $(OBJS)
	gcc -shared -o $@ $^
oezganEngine.o: oezganEngine.c
	gcc -c -fpic -o $@ $^

oezganEngineTester: oezganEngineTester.c
	gcc -o $@ $^ -lcrypto

.PHONY: clean
clean:
	rm -rf *.o *.so oezganEngineTester

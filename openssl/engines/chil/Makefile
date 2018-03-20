OBJS = e_chil.o

all: e_chil.so
.PHONY: all

e_chil.so: $(OBJS)
	gcc -shared -o $@ $^
e_chil.o: e_chil.c
	gcc -c -fpic -o $@ $^

.PHONY: clean
clean:
	rm -rf *.o e_chil.so
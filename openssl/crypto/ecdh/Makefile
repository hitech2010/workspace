# Quick instruction:
# To build against an OpenSSL built in the source tree, do this:
#
#    make OPENSSL_INCS_LOCATION=-I../../include OPENSSL_LIBS_LOCATION=-L../..
#
# To run the demos when linked with a shared library (default):
#
#    LD_LIBRARY_PATH=../.. ./aesccm
#    LD_LIBRARY_PATH=../.. ./aesgcm
OPENSSL_INCS_LOCATION=-I /usr/local/include
OPENSSL_LIBS_LOCATION=-L /usr/local/lib

CFLAGS = $(OPENSSL_INCS_LOCATION)
LDFLAGS = $(OPENSSL_LIBS_LOCATION) -lssl -lcrypto

all: ec 

ec: ec.o

ec:
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
.PHONY: clean
clean:
	rm -rf *.o ec

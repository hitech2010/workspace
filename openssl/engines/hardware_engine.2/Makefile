# Quick instruction:
# To build against an OpenSSL built in the source tree, do this:
#
#    make OPENSSL_INCS_LOCATION=-I../../include OPENSSL_LIBS_LOCATION=-L../..
#
# To run the demos when linked with a shared library (default):
#
#    LD_LIBRARY_PATH=../.. ./engineccm
#    LD_LIBRARY_PATH=../.. ./enginegcm
OPENSSL_INCS_LOCATION=-I /usr/local/include -I ./crypto/include
OPENSSL_LIBS_LOCATION=-L /usr/local/lib

CFLAGS = $(OPENSSL_INCS_LOCATION)
LDFLAGS = $(OPENSSL_LIBS_LOCATION) -lssl -lcrypto

all: engine 

engine: test.o

engine:
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

CC=gcc
CFLAGS=-g -Wall
LD_FLAGS=-lpthread -lpigpio -lrt

TARGET=MyServer
SRCDIR=../src
LIBSRCDIR=../../../lib/src
SRC=$(SRCDIR)/$(TARGET).c
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))
LIBSRCS=$(wildcard $(LIBSRCDIR)/*.c)
LIBOBJS=$(notdir $(patsubst %.c,%.o,$(LIBSRCS)))

$(TARGET) : $(OBJ) $(LIBOBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LD_FLAGS)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -o $@ -c $^ $(LD_FLAGS)

./%.o : $(LIBSRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(LD_FLAGS)

clean :
	rm -rf *.o
	rm -rf $(TARGET)

.PHONY : run clean

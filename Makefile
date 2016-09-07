
CFLAGS+=-O
CFLAGS+=-Wall -Werror
#CFLAGS+=-Wno-unused-function

LDFLAGS+=-lm

.PHONY: all clean world

all:: Assign5

Assign5: Assign5.o block.o
	$(LINK.cpp) -o $@ $^

clean::
	rm -f *.o Assign5

world:: clean all

Assign5.o:: Assign5.cpp block.h Assign5.h
block.cpp:: block.h



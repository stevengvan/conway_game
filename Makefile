.PHONY: clean
CPP= g++
CFLAGS= -Wall -Werror
OBJS= -o conway
SRC= conway.cpp
LIBS= -lncurses

conway:
	$(CPP) $(CFLAGS) $(OBJS) $(SRC) $(LIBS)

run: conway
	./conway

clean:
	rm -f conway

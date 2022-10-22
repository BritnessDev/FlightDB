# COMP2521 Assignment 1

# !!! DO NOT MODIFY THIS FILE !!!
# (except when changing CFLAGS1 on Line 17)

CC = clang
CFLAGS0 = -Wall -Werror -g # if you want to use valgrind
CFLAGS1 = -Wall -Werror -g -fsanitize=address,leak,undefined
CFLAGS2 = -Wall -Werror -g -fsanitize=memory,undefined

COMMON = FlightDb.c Tree.c List.c Record.c

.PHONY: all
all: testFlightDb

testFlightDb: testFlightDb.c $(COMMON)
	$(CC) $(CFLAGS1) -o testFlightDb testFlightDb.c $(COMMON)

.PHONY: clean
clean:
	rm -f testFlightDb


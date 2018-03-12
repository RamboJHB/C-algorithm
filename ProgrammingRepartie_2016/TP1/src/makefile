CC =gcc
LDFLAGS =
CFLAGS =-W -Wall -ansi -pedantic -Iinclude -std=c99

DIR=.
BIN=$(DIR)/bin/
OBJ=$(DIR)/obj/
INCLUDE=$(DIR)/include/
LIB=$(DIR)/lib/
SRC=$(DIR)/src/

HC=
O=

.SUFFIXES:
.PHONY: all clean test test-nfork test-mon_frere
all: $(BIN)nfork $(BIN)mon_frere $(OBJ)exec_sleep.o $(OBJ)repeat_nfork.o

test: test-nfork test-mon_frere

test-nfork: $(BIN)nfork
	-$$PWD/bin/nfork

test-mon_frere: $(BIN)mon_frere
	-$$PWD/bin/mon_frere

clean: 
	rm -rf $(OBJ)*.o $(BIN)*

$(BIN)%: $(OBJ)%.o $O
	@if [ -d $(BIN) ]; then : ; else mkdir $(BIN); fi
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ)%.o: $(SRC)%.c $(HC)
	@if [ -d $(OBJ) ]; then : ; else mkdir $(OBJ); fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(INCLUDE)%.h:
	@if [ -d $(INCLUDE) ]; then : ; else mkdir $(INCLUDE); fi


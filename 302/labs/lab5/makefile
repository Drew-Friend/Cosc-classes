
CC = g++
CFLAGS = -Wall
BIN = Friendnet1 Friendnet2 Friendnet3

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $* $<

clean:
	@rm -f $(BIN)
	@rm -f doknow?.txt mightknow?.txt

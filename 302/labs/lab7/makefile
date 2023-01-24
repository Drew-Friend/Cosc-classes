
CC = g++
CFLAGS = -g -Wall
BIN = Citysim

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN) 
	rm -f city_info.txt 
	rm -f city_dist.txt 
	rm -f city_time.txt 
	rm -f city_graph.txt 

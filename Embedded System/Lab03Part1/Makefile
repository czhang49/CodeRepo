
SERVER = lab03_server
SERVER_OBJS = $(SERVER).o pc_crc16.o

CC = gcc
CFLAGS = -I.. -g -Wall

all : server 

# Server (PC)
server : $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f *.o $(SERVER)


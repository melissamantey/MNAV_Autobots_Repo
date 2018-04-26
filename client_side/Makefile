CC = gcc
CFLAGS = -Wall -Wextra
DEPS = client.h
OBJ = client.o

%.o: %.c
	$(CC) -c $^ $(CFLAGS)
	
.PHONY: all
all: $(OBJ)
	$(CC) -o client $^ $(CFLAGS)

.PHONY: clean	
clean: 
	rm -f *.o *.gch client
	
.PHONY: new
new: clean all
	

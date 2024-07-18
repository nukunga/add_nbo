C=gcc
CFLAGS=-g -Wall
TARGET= add_nbo.out
OBJS= add_nbo.o
 
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

add_nbo.o :  add_nbo.cpp
	$(CC) -c -o  add_nbo.o  add_nbo.cpp

clean:
	rm $(OBJS) $(TARGET)
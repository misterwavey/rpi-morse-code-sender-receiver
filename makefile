TARGET = in

SRC = in.c

all: $(TARGET)
	sudo ./in

clean:
	-rm -f *.o
	-rm -f $(TARGET)

$(TARGET): 
	gcc -g -std=gnu99 -Wall -o $(TARGET) $(SRC) -lbcm2835


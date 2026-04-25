CC = gcc
SRC = main.c style.c
TARGET = lsi

install:
	$(CC) $(SRC) -o $(TARGET)
	sudo mv $(TARGET) /usr/local/bin/$(TARGET)

remove:
	sudo rm -f /usr/local/bin/$(TARGET)
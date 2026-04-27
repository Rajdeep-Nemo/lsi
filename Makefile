CC = gcc
SRC = main.c style.c sort.c detailed.c config.c tree.c
TARGET = lsi
INSTALL_DIR = $(HOME)/.local/bin

install:
	mkdir -p $(INSTALL_DIR)
	$(CC) $(SRC) -o $(TARGET)
	mv $(TARGET) $(INSTALL_DIR)/$(TARGET)

remove:
	rm -f $(INSTALL_DIR)/$(TARGET)
	rm -rf $(HOME)/.config/lsi
	@echo "lsi removed — binary and config deleted"
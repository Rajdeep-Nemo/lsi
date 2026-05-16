CC = gcc
SRC = main.c style.c sort.c detailed.c config.c tree.c
TARGET = lsi
INSTALL_DIR = $(HOME)/.local/bin

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

format:
	find . \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +

install: $(TARGET)
	mkdir -p $(INSTALL_DIR)
	mv $(TARGET) $(INSTALL_DIR)/$(TARGET)

remove:
	rm -f $(INSTALL_DIR)/$(TARGET)
	rm -rf $(HOME)/.config/lsi
	@echo "lsi: binary and config removed"
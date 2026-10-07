CC := gcc
LD := ld

BUILD := ../../build/kernel

CFLAGS := -ffreestanding -fno-stack-protector -mno-red-zone -O2 -Wall -Wextra

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SRC))

KERNEL := $(BUILD)/kmel.elf
LINKER_SCRIPT := linker.ld

all: $(KERNEL)

$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJ) $(LINKER_SCRIPT)
	mkdir -p $(BUILD)
	$(LD) -nostdlib -T $(LINKER_SCRIPT) $(OBJ) -o $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean

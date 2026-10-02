CC := gcc
LD := ld
OBJCOPY := objcopy

BUILD := ../../build/boot

CFLAGS := -ffreestanding -fno-stack-protector -fpic -fshort-wchar \
           -mno-red-zone -O2 -Wall -Wextra \
           -I/usr/include/efi -I/usr/include/efi/x86_64

EFI_LDS := /usr/lib/elf_x86_64_efi.lds

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SRC))

EFI_ELF := $(BUILD)/BOOTX64.so
BOOTLOADER := $(BUILD)/BOOTX64.EFI

all: $(BOOTLOADER)

$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(EFI_ELF): $(OBJ)
	mkdir -p $(BUILD)
	$(LD) -nostdlib -znocombreloc -T $(EFI_LDS) -shared -Bsymbolic \
		/usr/lib/crt0-efi-x86_64.o \
		$(OBJ) \
		-L/usr/lib -lefi -lgnuefi \
		-o $@

$(BOOTLOADER): $(EFI_ELF)
	$(OBJCOPY) \
		-j .text \
		-j .sdata \
		-j .data \
		-j .rodata \
		-j .dynamic \
		-j .dynsym \
		-j .rel \
		-j .rela \
		-j '.rel.*' \
		-j '.rela.*' \
		-j .reloc \
		--output-target=efi-app-x86_64 \
		--subsystem=10 \
		$< $@

clean:
	rm -rf $(BUILD)

.PHONY: all clean

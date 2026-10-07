BOOT_DIR := src/boot
KERNEL_DIR := src/kernel

BUILD := build
ISO_ROOT := $(BUILD)/iso

EFI_IMG := $(BUILD)/efiboot.img
ISO := $(BUILD)/mellow.iso

KERNEL := $(BUILD)/kernel/kmel.elf

all: $(ISO)

kernel:
	$(MAKE) -C $(KERNEL_DIR)

boot:
	$(MAKE) -C $(BOOT_DIR)

$(EFI_IMG): boot kernel
	mkdir -p $(dir $@)
	truncate -s 64M $@
	mkfs.fat -F 32 $@
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ $(BUILD)/boot/BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI
	mcopy -i $@ $(KERNEL) ::/kmel.elf

$(ISO): $(EFI_IMG) kernel
	mkdir -p $(ISO_ROOT)/EFI/BOOT
	cp $(EFI_IMG) $(ISO_ROOT)/EFI/BOOT/efiboot.img

	xorriso -as mkisofs \
		-R \
		-J \
		-V "MELLOW" \
		-o $@ \
		-eltorito-alt-boot \
		-e EFI/BOOT/efiboot.img \
		-no-emul-boot \
		$(ISO_ROOT)

clean:
	$(MAKE) -C $(BOOT_DIR) clean
	rm -rf $(BUILD)

.PHONY: all boot clean

BOOT_DIR := src/boot

BUILD := build
ISO_ROOT := $(BUILD)/iso

EFI_IMG := $(BUILD)/efiboot.img
ISO := $(BUILD)/mellow.iso

all: $(ISO)

boot:
	$(MAKE) -C $(BOOT_DIR)

$(EFI_IMG): boot
	mkdir -p $(dir $@)
	truncate -s 64M $@
	mkfs.fat -F 32 $@
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ $(BUILD)/boot/BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI

$(ISO): $(EFI_IMG)
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
	rm -rf $(BUILD)/iso $(EFI_IMG) $(ISO)

.PHONY: all boot clean

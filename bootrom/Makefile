
# We override some of the variables that we get from the Buildroot
# infrastructure here. Specifically, we don't want to use the provided
# CFLAGS since these assume that the build target isn't firmware-like
# (i.e. we want nostdlib, nostartfiles, etc).

override CFLAGS := \
	-DKEYSTONE_BOOTLOADER=1 \
	-DuECC_ENABLE_VLI_API=1 \
	-DuECC_CURVE=uECC_secp256r1 \
	-DuECC_SUPPORTS_secp160r1=0 \
	-DuECC_SUPPORTS_secp192r1=0 \
	-DuECC_SUPPORTS_secp224r1=0 \
	-DuECC_SUPPORTS_secp256r1=1 \
	-DuECC_SUPPORTS_secp256k1=0 \
	-mcmodel=medany \
	-nostdlib -nostartfiles -fno-common -std=gnu11 \
	-static \
	-fPIC \
	-O2 -Wall
O ?=.

# ^ consider taking out -g -Og and putting in -O2

bootloaders=\
	$(O)/bootrom.elf \
	$(O)/bootrom.bin

.PHONY: all
all: $(bootloaders)

.PHONY: clean
clean:
	rm -f $(bootloaders)

bootrom_sources = \
	./bootloader.S \
	./bootloader.c \
	${KEYSTONE_SM}/src/libcoap/src/oscore-ng/oscore_ng_sha_256.c \
	${KEYSTONE_SM}/src/libcoap/ext/micro-ecc/uECC.c \
	string.c

%.elf: $(bootrom_sources) bootloader.lds
	$(CC) \
		$(CFLAGS) \
		-I./ \
		-I${KEYSTONE_SM}/src/libcoap/ext/micro-ecc \
		-I${KEYSTONE_SM}/src/ \
		-L . \
		-T bootloader.lds \
		-o $@ $(bootrom_sources)

%.bin: %.elf
	$(OBJCOPY) -O binary --only-section=.text $< $@;


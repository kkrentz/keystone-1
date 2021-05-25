# Here, we just include the config.mk from the standard generic implementation
include $(src_dir)/platform/$(PLATFORM)/config.mk

# We do need to make sure to include headers for the SM
ifeq ($(KEYSTONE_SM),)
$(error KEYSTONE_SM not defined for SM)
endif

ifeq ($(KEYSTONE_SDK_DIR),)
$(error KEYSTONE_SDK_DIR not defined)
endif

platform-cflags-y = -I$(KEYSTONE_SDK_DIR)/include/shared \
                    -I$(KEYSTONE_SM)/src \
                    -I$(KEYSTONE_SM)/src/libcoap/ext/micro-ecc \
                    -I$(src_dir)/platform/$(PLATFORM)/include
platform-cflags-y += -DKEYSTONE_SM=1 \
                     -DuECC_CURVE=uECC_secp256r1 \
                     -DuECC_SUPPORTS_secp160r1=0 \
                     -DuECC_SUPPORTS_secp192r1=0 \
                     -DuECC_SUPPORTS_secp224r1=0 \
                     -DuECC_SUPPORTS_secp256r1=1 \
                     -DuECC_SUPPORTS_secp256k1=0 \
                     -DuECC_ENABLE_VLI_API=1

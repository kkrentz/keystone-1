#############
## Headers ##
#############

# General headers
keystone-sm-headers += sm_assert.h cpu.h enclave.h ipi.h mprv.h page.h platform-hook.h \
                        pmp.h safe_math_util.h sm.h sm-sbi.h sm-sbi-opensbi.h thread.h

# Crypto headers
ifneq ($(KEYSTONE_SM_NO_CRYPTO),y)
keystone-sm-headers += coap3/coap_internal.h \
                       crypto.h \
                       libcoap/ext/micro-ecc/uECC.h \
                       libcoap/src/oscore-ng/oscore_ng_sha_256.h
endif

# Platform headers
ifeq ($(KEYSTONE_PLATFORM),cva6)
    #for CVA6, the actual target platform is fpga/ariane, so PLATFORM variable is used
    keystone-sm-headers += platform/$(PLATFORM)/platform.h
else
    keystone-sm-headers += platform/$(KEYSTONE_PLATFORM)/platform.h
endif

ifeq ($(KEYSTONE_PLATFORM),sifive/fu540)
	keystone-sm-headers += platform/sifive/fu540/waymasks.h
endif

# Plugin headers
keystone-sm-headers += plugins/multimem.h plugins/plugins.h

##################
## Source files ##
##################

# Core files
keystone-sm-sources += attest.c cpu.c enclave.c pmp.c sm.c sm-sbi.c sm-sbi-opensbi.c \
                        thread.c mprv.c sbi_trap_hack.c trap.c ipi.c

# Crypto
ifneq ($(KEYSTONE_SM_NO_CRYPTO),y)
keystone-sm-sources += crypto.c \
                       libcoap/ext/micro-ecc/uECC.c \
                       libcoap/src/oscore-ng/oscore_ng_sha_256.c
endif

# Platform
keystone-sm-sources += platform/$(PLATFORM)/platform.c

# Plugin files
keystone-sm-sources += plugins/multimem.c plugins/plugins.c

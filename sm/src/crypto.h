//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <sbi/sbi_types.h>
#include "coap3/coap_internal.h"
#include "uECC.h"

typedef sha_256_context_t hash_ctx;
#define MDSIZE 32

#define SIGNATURE_SIZE (ECC_CURVE_P_256_SIZE * 2)
#define PRIVATE_KEY_SIZE (ECC_CURVE_P_256_SIZE)
#define PUBLIC_KEY_SIZE (ECC_CURVE_P_256_SIZE * 2)
#define PUBLIC_KEY_COMPRESSED_SIZE (1 + ECC_CURVE_P_256_SIZE)

typedef unsigned char byte;

extern byte sm_hash[MDSIZE];
extern byte sm_signature[SIGNATURE_SIZE];
extern byte sm_public_key[PUBLIC_KEY_SIZE];
extern byte sm_private_key[PRIVATE_KEY_SIZE];

void hash_init(hash_ctx* hash_ctx);
void hash_extend(hash_ctx* hash_ctx, const void* ptr, size_t len);
void hash_extend_page(hash_ctx* hash_ctx, const void* ptr);
void hash_finalize(void* md, hash_ctx* hash_ctx);

int kdf(const unsigned char* salt, size_t salt_len,
        const unsigned char* ikm, size_t ikm_len,
        const unsigned char* info, size_t info_len,
        unsigned char* okm, size_t okm_len);
#endif /* crypto.h */

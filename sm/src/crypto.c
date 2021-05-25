//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include "crypto.h"
#include "page.h"
#include "sm-sbi.h"

void hash_init(hash_ctx* ctx)
{
  SHA_256.init(ctx);
}

void hash_extend(hash_ctx* ctx, const void* ptr, size_t len)
{
  SHA_256.update(ctx, ptr, len);
}

void hash_extend_page(hash_ctx* ctx, const void* ptr)
{
  SHA_256.update(ctx, ptr, RISCV_PGSIZE);
}

void hash_finalize(void* md, hash_ctx* ctx)
{
  SHA_256.finalize(ctx, md);
}

int kdf(const unsigned char* salt, size_t salt_len,
        const unsigned char* ikm, size_t ikm_len,
        const unsigned char* info, size_t info_len,
        unsigned char* okm, size_t okm_len)
{
  if (okm_len > (255 * SHA_256_DIGEST_LENGTH)) {
    return -1;
  }
  sha_256_hkdf(salt, salt_len, ikm, ikm_len, info, info_len, okm, okm_len);
  return 0;
}

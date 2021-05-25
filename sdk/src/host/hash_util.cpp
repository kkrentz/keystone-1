//******************************************************************************
// Copyright (c) 2020, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
extern "C" {
#include "coap3/coap_internal.h"
}
#include "Memory.hpp"
#include "hash_util.hpp"

#define RISCV_PGSIZE (1 << 12)

void
hash_init(hash_ctx_t* hash_ctx) {
  SHA_256.init(hash_ctx);
}

void
hash_extend(hash_ctx_t* hash_ctx, const void* ptr, size_t len) {
  SHA_256.update(hash_ctx, (const uint8_t *)ptr, len);
}

void
hash_extend_page(hash_ctx_t* hash_ctx, const void* ptr) {
  SHA_256.update(hash_ctx, (const uint8_t *)ptr, RISCV_PGSIZE);
}

void
hash_finalize(void* md, hash_ctx_t* hash_ctx) {
  SHA_256.finalize(hash_ctx, (uint8_t *)md);
}

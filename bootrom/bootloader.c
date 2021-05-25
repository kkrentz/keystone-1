#include <stddef.h>
#include <stdint.h>
#include "coap3/coap_internal.h"
#include "string.h"
#include "uECC.h"

// Sanctum header fields in DRAM
extern uint8_t sanctum_dev_public_key[ECC_CURVE_P_256_SIZE * 2];
extern uint8_t sanctum_dev_secret_key[ECC_CURVE_P_256_SIZE];
unsigned int sanctum_sm_size = 0x1ff000;
extern uint8_t sanctum_sm_hash[SHA_256_DIGEST_LENGTH];
extern uint8_t sanctum_sm_public_key[ECC_CURVE_P_256_SIZE * 2];
extern uint8_t sanctum_sm_secret_key[ECC_CURVE_P_256_SIZE];
extern uint8_t sanctum_sm_signature[ECC_CURVE_P_256_SIZE * 2];
#define DRAM_BASE 0x80000000

/* Update this to generate valid entropy for target platform*/
int random_bytes(uint8_t *dest, unsigned size) {
#warning Bootloader does not have entropy source, keys are for TESTING ONLY
  static uint8_t counter;
  /* Gathering high quality entropy during boot on embedded devices is
   * a hard problem. Platforms taking security seriously must provide
   * a high quality entropy source available in hardware. Platforms
   * that do not provide such a source must gather their own
   * entropy. See the Keystone documentation for further
   * discussion. For testing purposes, we have no entropy generation.
   */
  for (unsigned i = 0; i < size; i++) {
    dest[i] = 0xac + (0xdd ^ counter++);
  }
  return 1;
}

void bootloader() {
  // TODO: on real device, copy boot image from memory. In simulator, HTIF writes boot image
  // ... SD card to beginning of memory.
  // sd_init();
  // sd_read_from_start(DRAM, 1024);

  /* On a real device, the platform must provide a secure root device
     keystore. For testing purposes we hardcode a known private/public
     keypair */
  // TEST Device key
  #include "use_test_keys.h"
  
  // Measure SM
  sha_256_hash((void*)DRAM_BASE, sanctum_sm_size, sanctum_sm_hash);

  // Generate SM key pair
  if (!uECC_make_key(sanctum_sm_public_key, sanctum_sm_secret_key, uECC_CURVE())) {
    while (1);
  }

  // Endorse the SM
  {
    sha_256_context_t hash_ctx;
    uint8_t digest[SHA_256_DIGEST_LENGTH];

    SHA_256.init(&hash_ctx);
    SHA_256.update(&hash_ctx, sanctum_sm_hash, sizeof(sanctum_sm_hash));
    SHA_256.update(&hash_ctx, sanctum_sm_public_key, sizeof(sanctum_sm_public_key));
    SHA_256.finalize(&hash_ctx, digest);
    // Sign (H_SM, PK_SM) with SK_D
    if (!uECC_sign(sanctum_dev_secret_key, digest, sizeof(digest), sanctum_sm_signature, uECC_CURVE())) {
      while (1);
    }
  }

  // Clean up
  // Erase SK_D
  memset((void*)sanctum_dev_secret_key, 0, sizeof(*sanctum_dev_secret_key));

  // caller will clean core state and memory (including the stack), and boot.
  return;
}

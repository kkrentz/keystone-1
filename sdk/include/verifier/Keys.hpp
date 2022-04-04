//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#pragma once

#include "coap3/coap_internal.h"
#include <string>

typedef unsigned char byte;

#define ATTEST_DATA_MAXLEN 1024
#define MDSIZE (SHA_256_DIGEST_LENGTH)
#define SIGNATURE_SIZE (ECC_CURVE_P_256_SIZE * 2)
#define PUBLIC_KEY_SIZE (ECC_CURVE_P_256_SIZE * 2)
#define PUBLIC_KEY_COMPRESSED_SIZE (1 + ECC_CURVE_P_256_SIZE)

class PublicKey {
 public:
  byte data[PUBLIC_KEY_SIZE];
  explicit PublicKey(std::string hexstr);
};

class DevicePublicKey : public PublicKey {
 public:
  explicit DevicePublicKey(std::string hexstr) : PublicKey(hexstr) {}
};

class SecurityMonitorPublicKey : public PublicKey {
 public:
  explicit SecurityMonitorPublicKey(std::string hexstr) : PublicKey(hexstr) {}
};

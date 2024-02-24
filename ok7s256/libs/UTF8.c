// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2023 YOUNGJIN JOO (neoelec@gmail.com)

#include <errno.h>
#include <stdbool.h>

#include "UTF8.h"

struct utf8_1byte {
  uint8_t code_0:7;
  uint8_t msb_0:1;
};

static bool __utf8_is_1byte(const void *__str)
{
  const struct utf8_1byte *utf8 = __str;

  if (utf8->msb_0 != 0)
    return false;

  return true;
}

static uint16_t __utf8_to_unicode_1(const void *__str)
{
  const struct utf8_1byte *utf8 = __str;

  return (uint16_t) utf8->code_0;
}

struct utf8_2bytes {
  uint8_t code_0:5;
  uint8_t msb_0:3;
  uint8_t code_1:6;
  uint8_t msb_1:2;
};

static bool __utf8_is_2_bytes(const void *__str)
{
  const struct utf8_2bytes *utf8 = __str;

  if (utf8->msb_0 != 0x6)
    return false;

  if (utf8->msb_1 != 0x2)
    return false;

  return true;
}

static uint16_t __utf8_to_unicode_2(const void *__str)
{
  const struct utf8_2bytes *utf8 = __str;
  uint16_t unicode;

  unicode = ((uint16_t) utf8->code_0) << 6;
  unicode |= (uint16_t) utf8->code_1;

  return unicode;
}

struct utf8_3bytes {
  uint8_t code_0:4;
  uint8_t msb_0:4;
  uint8_t code_1:6;
  uint8_t msb_1:2;
  uint8_t code_2:6;
  uint8_t msb_2:2;
};

static bool __utf8_is_3_bytes(const void *__str)
{
  const struct utf8_3bytes *utf8 = __str;

  if (utf8->msb_0 != 0xE)
    return false;

  if (utf8->msb_1 != 0x2)
    return false;

  if (utf8->msb_2 != 0x2)
    return false;

  return true;
}

static uint16_t __utf8_to_unicode_3(const void *__str)
{
  const struct utf8_3bytes *utf8 = __str;
  uint16_t unicode;

  unicode = ((uint16_t) utf8->code_0) << 12;
  unicode |= ((uint16_t) utf8->code_1) << 6;
  unicode |= (uint16_t) utf8->code_2;

  return unicode;
}

uint16_t utf8_to_unicode(const char *utf8_str, int *len)
{
  if (__utf8_is_1byte(utf8_str)) {
    *len = 1;
    return __utf8_to_unicode_1(utf8_str);
  } else if (__utf8_is_2_bytes(utf8_str)) {
    *len = 2;
    return __utf8_to_unicode_2(utf8_str);
  } else if (__utf8_is_3_bytes(utf8_str)) {
    *len = 3;
    return __utf8_to_unicode_3(utf8_str);
  }

  *len = -1;
  return (uint16_t) (*utf8_str);
}

union johab_char {
  struct {
    uint16_t jong:5;
    uint16_t joong:5;
    uint16_t cho:5;
    uint16_t msb:1;
  };
  uint16_t raw;
};

static uint16_t __unicode_to_johab(uint16_t kcode)
{
  uint16_t u_cho = kcode / (21 * 28);
  uint16_t u_joong = (kcode % (21 * 28)) / 28;
  uint16_t u_jong = (kcode % (21 * 28)) % 28;
  union johab_char __johab = {.raw = 0, };
  union johab_char *johab = &__johab;

  johab->msb = 1;
  johab->cho = u_cho + 2;
  johab->joong = u_joong + 3 + ((u_joong + 1) / 6) * 2;
  johab->jong = u_jong + 1 + (u_jong / 17);

  return johab->raw;
}

uint16_t unicode_to_johab(uint16_t unicode, int *err)
{
  uint16_t johab_char;

  if (unicode < 0xAC00 || unicode > 0xD7A3) {
    *err = -ENOENT;
    return unicode;
  }

  *err = 0;
  johab_char = __unicode_to_johab(unicode - 0xAC00);

  return (johab_char >> 8) | ((johab_char << 8) & 0xFF00);
}

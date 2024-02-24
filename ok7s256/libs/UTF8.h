// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2023 YOUNGJIN JOO (neoelec@gmail.com)

#ifndef __UTF8_H__
#define __UTF8_H__

#include <stdint.h>

extern uint16_t utf8_to_unicode(const char *utf8_str, int *len);
extern uint16_t unicode_to_johab(uint16_t unicode, int *err);

#endif /* __UTF8_H__ */

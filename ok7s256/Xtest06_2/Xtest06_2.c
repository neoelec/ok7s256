/* ========================================================================== */
/*                    Xtest06_2.c : Image Display on GLCD                     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>

const unsigned char screen1[1024] =            /* image data of screen 1 */
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3F, 0x78, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xFC, 0x7F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xFF, 0x7E, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x7C, 0x7E, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x1F, 0x78, 0x0E, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0x78, 0x06, 0xFC, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x78, 0x04, 0x7E, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x70, 0x04, 0x4D, 0x00, 0x00,
  0x00, 0x01, 0x7C, 0xF0, 0x02, 0x15, 0x80, 0x00,
  0x00, 0x07, 0x63, 0x00, 0x02, 0x0D, 0xC0, 0x00,
  0x00, 0x07, 0x40, 0x00, 0x02, 0x84, 0xE0, 0x00,
  0x00, 0x0F, 0x00, 0x00, 0x02, 0x80, 0x70, 0x00,
  0x00, 0x1F, 0x00, 0x00, 0x0A, 0x00, 0x30, 0x00,
  0x00, 0x1E, 0x00, 0x00, 0x04, 0x04, 0x38, 0x00,
  0x00, 0x3D, 0x40, 0x00, 0x04, 0x00, 0x1C, 0x00,
  0x00, 0x77, 0x70, 0x00, 0x08, 0x00, 0x1C, 0x00,
  0x00, 0xFF, 0x7C, 0x00, 0x00, 0x00, 0x3E, 0x00,
  0x00, 0xAF, 0x7C, 0x01, 0x40, 0x00, 0x2E, 0x00,
  0x01, 0xBF, 0x63, 0xC3, 0x00, 0x00, 0xFF, 0x00,
  0x01, 0xBF, 0x7F, 0xE0, 0x00, 0x00, 0x3B, 0x80,
  0x03, 0xBF, 0x7F, 0x88, 0x00, 0x00, 0x3D, 0x80,
  0x03, 0x3F, 0x7D, 0xFC, 0x00, 0x00, 0x3D, 0x80,
  0x02, 0xBF, 0x6F, 0x7E, 0x40, 0x00, 0x3C, 0xC0,
  0x07, 0xBF, 0x7F, 0x7F, 0x00, 0x00, 0x3F, 0x40,
  0x05, 0xBE, 0x7F, 0x7F, 0x00, 0x00, 0x36, 0xE0,
  0x0F, 0xBD, 0x7F, 0x7F, 0x00, 0x00, 0x1E, 0xE0,
  0x0B, 0xB7, 0x7F, 0x7E, 0x00, 0x00, 0x0E, 0xA0,
  0x1F, 0xAF, 0x7F, 0x70, 0x00, 0x00, 0x1E, 0xF0,
  0x17, 0xBF, 0x7F, 0x4C, 0x00, 0x00, 0x0A, 0xD0,
  0x3F, 0x3F, 0x7F, 0x3C, 0x00, 0x00, 0x0C, 0xF8,
  0x3F, 0xBF, 0x7F, 0x7E, 0x00, 0x00, 0x0A, 0x68,
  0x3E, 0xBF, 0x7F, 0xFC, 0x00, 0x00, 0x0E, 0xE8,
  0x3F, 0xBF, 0x7F, 0xE4, 0x00, 0x00, 0x06, 0xB4,
  0x39, 0xBF, 0x76, 0x78, 0x00, 0x00, 0x0E, 0xFC,
  0x27, 0xBF, 0x7E, 0x40, 0x00, 0x00, 0x0E, 0xEC,
  0x6F, 0xBC, 0x0F, 0xF0, 0x00, 0x00, 0x1E, 0xFC,
  0x77, 0xBC, 0x1E, 0x7E, 0x00, 0x00, 0x3E, 0xE4,
  0x7F, 0xB4, 0x1E, 0x7E, 0x00, 0x00, 0x1E, 0xF6,
  0x7F, 0xBE, 0x1E, 0x7B, 0x38, 0x00, 0x7A, 0xFA,
  0x6F, 0xBE, 0x03, 0xD7, 0x78, 0x00, 0x7E, 0xFE,
  0x4E, 0xB8, 0x0F, 0xFF, 0x60, 0x00, 0x7E, 0xF6,
  0x4D, 0xB0, 0x0A, 0x7F, 0x78, 0x00, 0x3E, 0x7E,
  0xFF, 0xB0, 0x1D, 0x7F, 0x5E, 0x70, 0x7E, 0xFE,
  0xFF, 0xB8, 0x0D, 0x7F, 0x6A, 0xE0, 0x7E, 0xDF,
  0xAF, 0xBC, 0x3F, 0x7F, 0x7E, 0xE0, 0x7E, 0xFF,
  0x8F, 0xBF, 0x7B, 0x7F, 0x7E, 0xE0, 0xFE, 0xF7,
  0xBF, 0xBF, 0x7F, 0x7F, 0x7E, 0x00, 0xFE, 0xF3,
  0xFF, 0xBF, 0x70, 0x00, 0x00, 0x71, 0xFE, 0xFD,
  0xFF, 0x98, 0x03, 0x7F, 0x7E, 0x80, 0x3E, 0xFF,
  0xF9, 0x1F, 0x2F, 0xFF, 0x7E, 0xF1, 0xF0, 0xFF,
  0xEF, 0xBF, 0x7F, 0x7F, 0x7E, 0xF1, 0xFE, 0xAF,
  0xBF, 0xBF, 0x7F, 0x7F, 0x7E, 0xF9, 0xFE, 0xF1,
  0xFF, 0xBF, 0x7F, 0x7F, 0x7E, 0xFD, 0xFE, 0xFF,
  0xFF, 0xBF, 0x7F, 0x7F, 0x7E, 0x7D, 0xFE, 0xFF,
  0xBF, 0xBF, 0x7F, 0x7F, 0x7E, 0xA5, 0xFE, 0xF1,
  0xCF, 0xBF, 0x7F, 0x7F, 0x7E, 0xA1, 0xFE, 0xDF,
  0xE1, 0xBF, 0x7F, 0x7F, 0x7E, 0xC1, 0x7C, 0x77,
  0xFF, 0xA1, 0x7F, 0x7F, 0x7E, 0xE0, 0x0E, 0xF5,
  0xBF, 0xBE, 0x00, 0x06, 0x02, 0x80, 0x7E, 0xFB,
  0xBF, 0xBF, 0x7F, 0x7F, 0x7E, 0xE0, 0xFE, 0xFF,
  0x9F, 0xBF, 0x7F, 0x7F, 0x7E, 0xC0, 0xFE, 0xF7,
  0xEF, 0xBF, 0x7F, 0x7F, 0x40, 0x80, 0xFE, 0xF6,
  0x67, 0xBF, 0x7F, 0x7E, 0x00, 0x01, 0xFE, 0xDE,
  0x5B, 0xBF, 0x7F, 0x7E, 0x00, 0x01, 0xFE, 0xBA,
  0x7D, 0xBF, 0x7F, 0x78, 0x00, 0x00, 0xFE, 0xFE,
  0x7F, 0x3F, 0x7F, 0x70, 0x00, 0x01, 0x7C, 0xFE,
  0x7F, 0x9F, 0x7F, 0x70, 0x00, 0x01, 0x32, 0xF4,
  0x2F, 0xAF, 0x7F, 0xE6, 0x00, 0x00, 0x0E, 0xF4,
  0x27, 0xB9, 0x7F, 0xC6, 0x00, 0x00, 0x3E, 0xE4,
  0x3F, 0xBF, 0x3B, 0xDF, 0x00, 0x00, 0x1E, 0xFC,
  0x3F, 0xBF, 0x61, 0xBA, 0x00, 0x01, 0xDE, 0xFC,
  0x3C, 0x0F, 0x40, 0x00, 0x00, 0x71, 0x1E, 0xBC,
  0x38, 0x00, 0x00, 0x2B, 0x00, 0x71, 0x3E, 0xF8,
  0x1F, 0x00, 0x00, 0x23, 0x60, 0xF8, 0x8E, 0x78,
  0x1F, 0xA0, 0x00, 0x3F, 0x70, 0x08, 0xAE, 0xF8,
  0x17, 0x90, 0x00, 0x7F, 0x78, 0x04, 0x9E, 0xD8,
  0x1F, 0xB0, 0x00, 0xFF, 0x78, 0x10, 0xCA, 0xF0,
  0x1B, 0xB8, 0x01, 0xFF, 0x7C, 0x79, 0xEE, 0xB0,
  0x0F, 0xBA, 0x03, 0x7F, 0x78, 0xFD, 0x8E, 0xE0,
  0x0D, 0xBC, 0x03, 0x7F, 0x7E, 0xFD, 0x8E, 0xE0,
  0x07, 0xBE, 0x07, 0x7F, 0x7E, 0xFD, 0x1F, 0x40,
  0x06, 0xBF, 0x4F, 0x7F, 0x7E, 0xC0, 0x0E, 0xC0,
  0x03, 0x3F, 0x73, 0x7F, 0x7E, 0x80, 0x0D, 0x80,
  0x03, 0x3F, 0x7D, 0x7F, 0x7E, 0x80, 0x0D, 0x80,
  0x01, 0xBF, 0x7E, 0x60, 0x0C, 0x70, 0x0B, 0x80,
  0x01, 0x9F, 0x7F, 0x7F, 0x7E, 0xF8, 0x0F, 0x00,
  0x00, 0xBF, 0x7F, 0x7F, 0x7E, 0xF8, 0x0E, 0x00,
  0x00, 0xF7, 0x7F, 0x7F, 0x7E, 0xFC, 0x0E, 0x00,
  0x00, 0x7F, 0x7F, 0x7F, 0x7E, 0xEC, 0x1C, 0x00,
  0x00, 0x5D, 0x7F, 0x7F, 0x7E, 0xFD, 0x58, 0x00,
  0x00, 0x3F, 0x7F, 0x7F, 0x7E, 0xFD, 0xD8, 0x00,
  0x00, 0x1F, 0x7F, 0x7F, 0x7E, 0xFD, 0xF0, 0x00,
  0x00, 0x0F, 0x5F, 0x7F, 0x7E, 0xFD, 0xE0, 0x00,
  0x00, 0x07, 0x7F, 0x7F, 0x7E, 0xF5, 0xE0, 0x00,
  0x00, 0x03, 0x73, 0x7F, 0x7E, 0x9D, 0xC0, 0x00,
  0x00, 0x01, 0x7C, 0x7F, 0x7C, 0x7D, 0x80, 0x00,
  0x00, 0x01, 0xFF, 0x60, 0x16, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x7F, 0x7E, 0xFE, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0x7F, 0x7E, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x1F, 0x7F, 0x7E, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xFF, 0x7E, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xFF, 0x7F, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0x7E, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char screen2[1024] =            /* image data of screen 2 */
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x32, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7D, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xF7, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xA8, 0xC0, 0x00, 0x00, 0x18,
  0x00, 0x00, 0x01, 0x90, 0x20, 0x00, 0x00, 0x38,
  0x00, 0x00, 0x03, 0x20, 0x10, 0x00, 0x00, 0xF8,
  0x00, 0x00, 0x03, 0x10, 0x08, 0x00, 0x01, 0xF0,
  0x00, 0x00, 0x03, 0xB0, 0x04, 0x00, 0x03, 0xB0,
  0x00, 0x00, 0x01, 0xA8, 0x02, 0x00, 0x0E, 0x30,
  0x00, 0x00, 0x03, 0xA8, 0x02, 0x00, 0x18, 0x60,
  0x00, 0x00, 0x03, 0x2C, 0x01, 0x00, 0x70, 0x40,
  0x00, 0x00, 0x03, 0x14, 0x21, 0x00, 0xC0, 0x40,
  0x00, 0x00, 0x06, 0x16, 0x71, 0x03, 0x00, 0xC0,
  0x00, 0x00, 0x06, 0x12, 0x71, 0x07, 0x00, 0xC0,
  0x00, 0x00, 0x07, 0x0A, 0x70, 0x8C, 0x03, 0x80,
  0x00, 0x18, 0x07, 0x89, 0x20, 0x98, 0x03, 0x00,
  0x00, 0x1C, 0x07, 0x8D, 0x00, 0xF8, 0x0E, 0x00,
  0x00, 0x1C, 0x07, 0x85, 0x01, 0xE0, 0x1E, 0x00,
  0x00, 0x1E, 0x0F, 0xC5, 0x00, 0xFC, 0x3C, 0x00,
  0x00, 0x1E, 0x0F, 0xC4, 0x00, 0x07, 0xF8, 0x00,
  0x00, 0x1E, 0x1F, 0x00, 0x00, 0x00, 0x30, 0x00,
  0x00, 0x1F, 0x7E, 0x00, 0x00, 0x00, 0x1C, 0x00,
  0x00, 0x1F, 0x7E, 0x00, 0x00, 0x00, 0x0C, 0x00,
  0x03, 0x1F, 0xFC, 0x00, 0x00, 0x1E, 0x03, 0x00,
  0x07, 0x9F, 0xF0, 0x00, 0x00, 0x0F, 0xF1, 0x80,
  0x06, 0xDF, 0xE0, 0x00, 0x00, 0x07, 0xFD, 0xC0,
  0x0E, 0x7F, 0xC0, 0x00, 0x09, 0xE3, 0xFE, 0x40,
  0x0C, 0x3F, 0xC0, 0x00, 0x0B, 0x33, 0xFF, 0xB0,
  0x0C, 0x1F, 0xC0, 0x00, 0x0F, 0x19, 0xFF, 0xB0,
  0x0E, 0x17, 0x80, 0x00, 0x0E, 0x1F, 0xFF, 0xD8,
  0x09, 0x27, 0x80, 0x00, 0x06, 0x0F, 0xFF, 0xD8,
  0x09, 0xB7, 0x00, 0x00, 0x02, 0x07, 0xFF, 0xFC,
  0x08, 0x1F, 0x00, 0x00, 0x03, 0x03, 0xFF, 0xF6,
  0x0C, 0x1F, 0x00, 0x00, 0x01, 0x03, 0xFF, 0xF6,
  0x04, 0x07, 0x80, 0x00, 0x01, 0x80, 0x7F, 0xFB,
  0x04, 0x01, 0x80, 0x00, 0x00, 0x80, 0x0F, 0xF9,
  0x06, 0x01, 0x80, 0x00, 0x00, 0xC0, 0x00, 0xFF,
  0x06, 0x00, 0x80, 0x00, 0x00, 0xC0, 0x00, 0x00,
  0x07, 0x00, 0x80, 0x00, 0x00, 0xC0, 0x00, 0x00,
  0x07, 0x00, 0x80, 0x00, 0x00, 0xC0, 0x00, 0x00,
  0x01, 0x80, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00,
  0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00,
  0x01, 0xE0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x38, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x1C, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x1C, 0x00, 0x80, 0x01, 0x80, 0x00, 0x00,
  0x00, 0x0F, 0x01, 0x00, 0x00, 0xC0, 0x00, 0x00,
  0x00, 0x0F, 0x86, 0x00, 0x00, 0xC0, 0x00, 0x00,
  0x00, 0x0F, 0xE8, 0x00, 0x00, 0x60, 0x00, 0x00,
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x20, 0x00, 0x00,
  0x1F, 0x0E, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
  0x19, 0x8E, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x30, 0xCE, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x78, 0x6E, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
  0x64, 0x2E, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
  0x42, 0x2F, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00,
  0x60, 0x2F, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x50, 0x2F, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x48, 0x7F, 0x80, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x20, 0x7F, 0x80, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x30, 0x7F, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x30, 0x7E, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x10, 0x30, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x18, 0x30, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x08, 0x00, 0x40, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x0C, 0x00, 0x80, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x07, 0xC0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00,
  0x01, 0x80, 0xE0, 0x00, 0x00, 0x1C, 0x00, 0x00,
  0x01, 0x8F, 0xE0, 0x00, 0x00, 0x18, 0x00, 0x00,
  0x01, 0xCB, 0xE0, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0xFB, 0xF0, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0x00, 0x00, 0x60, 0x00, 0x00,
  0x00, 0x00, 0xF8, 0x06, 0x00, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0xF0, 0x0E, 0x01, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7C, 0x01, 0xF8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFB, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xD9, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC8, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0x30, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x88, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xCC, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xCC, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xF1, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char screen3[1024] =            /* image data of screen 3 */
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xFD, 0x43, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x21, 0x41, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x0C, 0x41, 0xC2, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x41, 0x42, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x81, 0xF8, 0xA0, 0x00, 0x00, 0x00,
  0x00, 0x30, 0xFF, 0xE1, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x03, 0xFE, 0x20, 0x00, 0x00, 0x00,
  0x00, 0xE1, 0xF9, 0x0C, 0x20, 0x00, 0x00, 0x00,
  0x01, 0xC1, 0x64, 0x86, 0x20, 0x00, 0x00, 0x00,
  0x01, 0xC2, 0x4A, 0x41, 0xA0, 0x00, 0x00, 0x00,
  0x03, 0xC2, 0x8A, 0x40, 0xE0, 0x00, 0x00, 0x00,
  0x03, 0x82, 0x8A, 0x40, 0x20, 0x00, 0x00, 0x00,
  0x03, 0x84, 0x92, 0x40, 0x30, 0x00, 0x00, 0x00,
  0x07, 0x84, 0x92, 0x42, 0x10, 0x00, 0x00, 0x00,
  0x07, 0x04, 0x9C, 0x85, 0x88, 0x00, 0x00, 0x00,
  0x07, 0x07, 0x71, 0x83, 0x88, 0x00, 0x00, 0x00,
  0x07, 0x08, 0x03, 0x00, 0xCC, 0x00, 0x00, 0x00,
  0x0F, 0x08, 0x06, 0x00, 0x44, 0x00, 0x00, 0x00,
  0x0A, 0x08, 0x38, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x0E, 0x0F, 0xC0, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x0E, 0x0F, 0xFC, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0E, 0x08, 0x0F, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x0E, 0x08, 0x25, 0xC0, 0x02, 0x00, 0x00, 0x00,
  0x1E, 0x10, 0x48, 0x60, 0x02, 0x00, 0x00, 0x00,
  0x0F, 0x60, 0x50, 0x30, 0x02, 0x00, 0x00, 0x00,
  0x1D, 0x80, 0x90, 0x28, 0x02, 0x00, 0x00, 0x00,
  0x10, 0x80, 0x10, 0x28, 0x02, 0x00, 0x00, 0x00,
  0x20, 0x80, 0x50, 0x6C, 0x02, 0x00, 0x00, 0x00,
  0x63, 0x80, 0x58, 0xCC, 0x06, 0x00, 0x00, 0x00,
  0x48, 0x40, 0x3F, 0x16, 0x04, 0x00, 0x00, 0x00,
  0x50, 0x38, 0x18, 0x62, 0x06, 0x00, 0x00, 0x00,
  0xA0, 0x0F, 0x87, 0x82, 0x05, 0x00, 0x00, 0x00,
  0x80, 0x00, 0xE0, 0x02, 0x03, 0x00, 0x00, 0x00,
  0x80, 0x38, 0x10, 0x02, 0x0D, 0x00, 0x00, 0x08,
  0x80, 0x46, 0x18, 0x02, 0x03, 0x07, 0xB0, 0x3C,
  0x80, 0xA5, 0x08, 0x06, 0x1D, 0x18, 0xC8, 0x22,
  0x80, 0x01, 0x0C, 0x04, 0x36, 0x38, 0x4C, 0x62,
  0x80, 0x81, 0x04, 0x04, 0x24, 0x50, 0x74, 0x41,
  0x80, 0x81, 0x04, 0x0C, 0x78, 0xD0, 0x36, 0x41,
  0x40, 0x7E, 0x04, 0x08, 0xC5, 0x11, 0x92, 0x41,
  0x40, 0x18, 0x08, 0x19, 0x75, 0x13, 0xD3, 0x41,
  0x20, 0x00, 0x08, 0x11, 0xE6, 0x00, 0x22, 0x81,
  0x20, 0x00, 0x08, 0x21, 0x26, 0x47, 0xAA, 0x81,
  0x10, 0x00, 0x10, 0x23, 0x1E, 0x47, 0x6A, 0xC1,
  0x2C, 0x00, 0x70, 0x42, 0xD4, 0xC4, 0x22, 0xC1,
  0x0F, 0x80, 0xE0, 0x86, 0x25, 0xC4, 0x23, 0xC1,
  0x0F, 0xFB, 0xC0, 0x85, 0x85, 0xC3, 0xD3, 0x01,
  0x07, 0xBF, 0x81, 0x05, 0x05, 0x78, 0x33, 0x01,
  0x0B, 0x80, 0x01, 0x08, 0x74, 0x88, 0x22, 0x01,
  0x07, 0x80, 0x02, 0x08, 0x04, 0x00, 0x40, 0x01,
  0x07, 0x80, 0x02, 0x0F, 0xDE, 0x00, 0x80, 0x02,
  0x07, 0x80, 0x04, 0x0F, 0xF6, 0x0B, 0x00, 0x06,
  0x07, 0x80, 0x04, 0x08, 0xD5, 0x4C, 0x00, 0x04,
  0x17, 0x80, 0x04, 0x09, 0x0D, 0x48, 0x00, 0x08,
  0x1F, 0x80, 0x04, 0x0A, 0x6C, 0xC8, 0x00, 0x10,
  0x0F, 0xC0, 0x02, 0x04, 0x34, 0x48, 0x00, 0x60,
  0x0F, 0xC0, 0x02, 0x06, 0x64, 0x58, 0x00, 0xC0,
  0x03, 0xC0, 0x03, 0x03, 0xC6, 0x10, 0x03, 0x80,
  0x16, 0x20, 0x01, 0x00, 0x05, 0xF8, 0x0E, 0x00,
  0x06, 0xF8, 0x01, 0x80, 0x08, 0x1F, 0xF8, 0x00,
  0x05, 0x07, 0x80, 0x44, 0x70, 0x00, 0x00, 0x00,
  0x0A, 0x01, 0xC0, 0x67, 0xD0, 0x00, 0x00, 0x00,
  0x0C, 0x00, 0x30, 0x20, 0x10, 0x00, 0x0C, 0x00,
  0x18, 0x00, 0x08, 0x10, 0x10, 0x00, 0xC0, 0x00,
  0x18, 0x0F, 0x08, 0x10, 0x20, 0x08, 0x00, 0x00,
  0x18, 0x3E, 0x84, 0x08, 0x60, 0x03, 0xC0, 0x00,
  0x08, 0x28, 0x84, 0x08, 0xC0, 0x00, 0x00, 0x00,
  0x08, 0x20, 0x82, 0x0D, 0x80, 0x00, 0x00, 0x00,
  0x08, 0x11, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x0E, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x80, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xE0, 0x38, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xD7, 0xF0, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xDF, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xD0, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xDA, 0x00, 0xD0, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x89, 0xFF, 0x60, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0A, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x1B, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x20, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x20, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x20, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x20, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x14, 0x41, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0E, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x06, 0x5E, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void GLCD_draw(unsigned int number)
{                                              /* draw a GLCD screen */
  unsigned int i, j;

  for (i = 0; i <= 7; i++) {
    GLCD_command(GLCD_CS2 | GLCD_CS1, 0xB8 + (7 - i));  // X addtess
    GLCD_command(GLCD_CS1, 0x40);              // Y start address of CS1
    for (j = 0; j <= 63; j++) {                // draw CS1 data
      if (number == 1)
        GLCD_data(GLCD_CS1, screen1[i + j * 8]);
      else if (number == 2)
        GLCD_data(GLCD_CS1, screen2[i + j * 8]);
      else if (number == 3)
        GLCD_data(GLCD_CS1, screen3[i + j * 8]);
    }
    GLCD_command(GLCD_CS2, 0x40);              // Y start address of CS2
    for (j = 64; j <= 127; j++) {              // draw CS2 data
      if (number == 1)
        GLCD_data(GLCD_CS2, screen1[i + j * 8]);
      else if (number == 2)
        GLCD_data(GLCD_CS2, screen2[i + j * 8]);
      else if (number == 3)
        GLCD_data(GLCD_CS2, screen3[i + j * 8]);
    }
  }
}

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, " Image Graphic  ");        // display title on text LCD
  LCD_string(0xC0, "   screen(0)    ");
  Beep();

  while (1) {
    for (i = 1; i <= 3; i++) {                 // draw screen 1, 2, 3
      LCD_command(0xCA);
      LCD_data(i + '0');
      GLCD_draw(i);
      Delay_ms(3000);
    }
  }
}

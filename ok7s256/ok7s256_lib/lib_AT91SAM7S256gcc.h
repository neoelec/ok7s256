#ifndef __LIB_AT91SAM7S256GCC_H__
#define __LIB_AT91SAM7S256GCC_H__

/* FIXME: to prevent linker errors */
#define __inline static inline

#include "lib_AT91SAM7S256.h"

__inline void AT91F_PIO_Opendrain(		/* configure open drain */
	AT91PS_PIO pPio, unsigned int multiDrvEnable)
{
//	pPio->PIO_MDDR = ~multiDrvEnable;
	pPio->PIO_MDER = multiDrvEnable;
}

__inline void AT91F_PIO_Pullup(			/* configure pull up */
	AT91PS_PIO pPio, unsigned int pullupEnable)
{
//	pPio->PIO_PPUDR = ~pullupEnable;
	pPio->PIO_PPUER = pullupEnable;
}

#undef __inline

#endif /* __LIB_AT91SAM7S256GCC_H__ */

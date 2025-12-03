/**
 * Copyright (c) 2025 OwlTech
 *
 * \file common_def.h
 * \brief
 * \author OwlTech
 * \date Nov 3, 2025
 */

#ifndef COMMON_DEF_H_
#define COMMON_DEF_H_

/******************************************************************************/
/*--------------------------Includes------------------------------------------*/
/******************************************************************************/
#include <stdint.h>

#include "fw_debug.h"

/******************************************************************************/
/*--------------------------Defines-------------------------------------------*/
/******************************************************************************/
#define ENABLE			1u
#define DISABLE			0u

#define BYTES             		(1u)              	//!< size of a byte
#define HALF_WORDS        		(2u * BYTES)    	//!< size of an (32-bit) word
#define WORDS             		(4u * BYTES)    	//!< size of an (32-bit) word
#define DWORDS            		(8u * BYTES)    	//!< size of an (64-bit) double word
#define KILO_BYTES        		(1024u * BYTES) 	//!< size of 1024 bytes (1 kByte)
#define NUM_OF_NIBBLE_BITS 		(4u * BYTES)    	//!< Number of bits inside an (4-bit) half Byte
#define NUM_OF_BYTE_BITS  		(8u * BYTES)    	//!< Number of bits inside an (8-bit) Byte
#define NUM_OF_HALF_WORD_BITS  	(8u * HALF_WORDS)	//!< Number of bits inside a (16-bit) half word
#define NUM_OF_WORD_BITS  		(8u * WORDS)    	//!< Number of bits inside an (32-bit) word
#define NUM_OF_DWORD_BITS 		(8u * DWORDS)   	//!< Number of bits inside an (64-bit) double-word
#define NBYTES_PER_WORD   		(4u)              	//!< Number of bytes in an (32-bit) word

#define NUM_OF_ARRAY(x)   (sizeof(x) / sizeof(*x))   //!< Number of an array elements

#define INTENTINALLY_UNUSED(x)	((void)x)

#define ERR_STAT_NO_ERROR		(0u)


#define __WEAK 	__attribute__((weak))


/******************************************************************************/
/*--------------------------Data Structures-----------------------------------*/
/******************************************************************************/
/** \brief Data Template */
	/**< Data 1. */
	//!< Data 2.
typedef _Bool t_bool;  //!< Standard boolean datatype
#define FALSE (1 == 0) //!< false
#define TRUE  (!FALSE) //!< true

/** \brief Error codes. */
typedef enum {
    e_ec_no_error = 0u,     //!< Status success
    e_ec_unspecified_error, //!< Status unspecified Error
    e_ec_invalid_param,     //!< Status invalid parameter
	e_ec_timeout	     	//!< Status timeout
} t_error_code;

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */
static inline uint32_t b_to_uint32(const t_bool b);

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/
static inline uint32_t b_to_uint32(const t_bool b)
{
    /**
     *  \paramrange{b,FALSE,disable}
     *  \paramrange{b,TRUE,enable}
     */
    // convert t_bool to uint32_t
    /** \activity convert t_bool to uint32_t. */
    const uint8_t ret = (b != FALSE) ? 1u : 0u; /* polyspace RTE:UNR [Not a defect:Low] "Low-level function" */
    return (uint32_t)ret;
}


/******************************************************************************/
/*---------------------------API Function Prototypes--------------------------*/
/******************************************************************************/
/** \brief 
 *  \param 
 *  \return 
 *  	\retval 
 */

#endif /* COMMON_DEF_H_ */
/*** EOF ***/

/*
 * fw_debug.h
 *
 *  Created on: Jun 11, 2025
 *      Author: bagolyzsolt
 */

#ifndef COMMON_FW_DEBUG_H_
#define COMMON_FW_DEBUG_H_

#define OPEN_OCD_EN

#define DEBUG_PRINT \
	(void)printf

#ifdef OPEN_OCD_EN
	extern void initialise_monitor_handles();
#endif /* OPEN_OCD_EN */



#endif /* COMMON_FW_DEBUG_H_ */

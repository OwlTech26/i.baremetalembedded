/*
 * led.h
 *
 *  Created on: Dec 20, 2023
 *      Author: bagolyzsolt
 */

#ifndef LED_H_
#define LED_H_

#define LED_USR  5 // PA5

#define DELAY_COUNT_1MS 		 1250U
#define DELAY_COUNT_1S  		(1000U * DELAY_COUNT_1MS)
#define DELAY_COUNT_500MS  		(500U  * DELAY_COUNT_1MS)
#define DELAY_COUNT_250MS 		(250U  * DELAY_COUNT_1MS)
#define DELAY_COUNT_125MS 		(125U  * DELAY_COUNT_1MS)

void LED_init(void);
void LED_on(const uint32_t led_no);
void LED_off(const uint32_t led_no);
void LED_delay(const uint32_t count);


#endif /* LED_H_ */

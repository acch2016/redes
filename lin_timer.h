/*
 * lin_timer.h
 *
 *  Created on: Mar 4, 2019
 *      Author: Cursos
 */

#ifndef LIN_TIMER_H_
#define LIN_TIMER_H_

typedef enum {lin_pit0,lin_pit1} lin_pit_t;

//typedef struct
//{
//	lin_pit_t pit;
//
//}lin_pit_config_t;

void lin_pit_init(lin_pit_t base, float period);

#endif /* LIN_TIMER_H_ */

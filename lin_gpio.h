/*
 * lin_gpio.h
 *
 *  Created on: Mar 4, 2019
 *      Author: Cursos
 */

#ifndef LIN_GPIO_H_
#define LIN_GPIO_H_

#include <stdint.h>

typedef enum {rtos_gpioA,rtos_gpioB,rtos_gpioC,rtos_gpioD,rtos_gpioE} rtos_gpio_t;
typedef enum {rtos_gpio_portA,rtos_gpio_portB,rtos_gpio_portC,rtos_gpio_portD,rtos_gpio_portE} rtos_gpio_port_t;
typedef enum {rtos_gpio_input,rtos_gpio_output} rtos_gpio_direction_t;
typedef enum {rtos_gpio_sucess,rtos_gpio_fail} rtos_gpio_flag_t;

typedef struct
{
	rtos_gpio_t gpio;
	rtos_gpio_port_t port;
	uint32_t pin; //pin user wants to read
	rtos_gpio_direction_t pin_direction;//

}rtos_gpio_config_t;

rtos_gpio_flag_t rtos_gpio_init(rtos_gpio_config_t config);

//TODO Esta función recibira la estructura tipo rtos_gpio_config_t de donde obtendria el pin y el puerto
rtos_gpio_flag_t rtos_gpio_wait_pin(rtos_gpio_config_t config);
//TODO Declarar aqui la otra función que controlará al LED
uint8_t rtos_gpio_toogle_pin(rtos_gpio_config_t config, uint8_t modo_administrador);

#endif /* LIN_GPIO_H_ */

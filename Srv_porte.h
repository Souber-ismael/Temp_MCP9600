/*
 * Svr_porte.h
 *
 *  Created on: 25 août 2025
 *      Author: User
 */

#ifndef MAIN_SRV_PORTE_H_
#define MAIN_SRV_PORTE_H_

#include <stdbool.h>
#include <stdint.h>
#define DOOR_GPIO 4
// Initialize door GPIO
void door_init(int gpio_num);

// Update door state (call it regularly in loop or task)
void door_update(void);

// Get current state of door (true=open, false=closed)
bool door_is_open(void);

// Get how long door has been open (ms)
int64_t door_get_open_duration(void);

#endif /* MAIN_SRV_PORTE_H_ */

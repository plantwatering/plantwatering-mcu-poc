#ifndef __VALVE_CONSOLE_H
#define __VALVE_CONSOLE_H

/**
 * @brief Init a new valve console driver. This function will allocates a new driver in drv
 * @param drv A pointer to a valve_driver
 * @return errno if error, 0 otherwise
 */
int valve_console_init(struct valve_driver *drv);

/**
 * @brief Deinit a console valve
 * @param drv A previously init'd valve console
 */
void valve_console_deinit(struct valve_driver *drv);

#endif // __VALVE_CONSOLE_H

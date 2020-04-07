#ifndef __VALVE_CONSOLE_H
#define __VALVE_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Init a new valve console driver. This function will allocates a new driver in drv
 * @param drv An uninitialized pointer
 * @return errno if error, 0 otherwise
 */
int valve_console_init(struct valve_driver *drv);

#ifdef __cplusplus
}
#endif

#endif // __VALVE_CONSOLE_H

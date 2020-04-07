#ifndef __VALVE_MOCK_H
#define __VALVE_MOCK_H

/**
 * @brief Init a new valve console driver. This function will allocates a new driver in drv
 * @param drv A pointer to a valve_driver
 * @return errno if error, 0 otherwise
 */
int valve_mock_init(struct valve_driver *drv);

/**
 * @brief Deinit a console valve
 * @param drv A previously init'd valve console
 */
void valve_mock_deinit(struct valve_driver *drv);

#endif // __VALVE_MOCK_H

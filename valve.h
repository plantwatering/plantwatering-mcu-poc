#ifndef __VALVE_H
#define __VALVE_H

#include <stdbool.h>
#include "valve_driver.h"

struct valve {
    int (*set)(struct valve *v, bool value);
    int (*get)(const struct valve *v, bool *value);
    void (*notificate)(const struct valve *v, bool value);
    struct valve_driver *drv;
};

/**
 * @brief Init a new valve logic. This function will allocates a new valve in v
 * @param v An uninitialized pointer
 * @return errno if error, 0 otherwise
 */
int valve_init(struct valve *v, struct valve_driver *drv);

#endif // __VALVE_H

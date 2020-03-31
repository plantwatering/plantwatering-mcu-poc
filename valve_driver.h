#ifndef __VALVE_DRIVER_H
#define __VALVE_DRIVER_H

#include <stdbool.h>

struct valve_driver {
    int (*open)(struct valve_driver* drv);
    int (*close)(struct valve_driver* drv);
    int (*get_state)(const struct valve_driver* drv, bool *value);
    void *priv;
};

#endif // __VALVE_DRIVER_H

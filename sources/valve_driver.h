#ifndef __VALVE_DRIVER_H
#define __VALVE_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct valve_driver {
    int (*open)(struct valve_driver* drv);
    int (*close)(struct valve_driver* drv);
    int (*get_state)(const struct valve_driver* drv, bool *value);
    void *priv;
};

#ifdef __cplusplus
}
#endif

#endif // __VALVE_DRIVER_H

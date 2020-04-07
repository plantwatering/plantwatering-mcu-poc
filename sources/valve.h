#ifndef __VALVE_H
#define __VALVE_H

#ifdef __cplusplus
extern "C" {
#endif

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
 * @param v A pointer to valve structure
 * @param drv A pointer to valve_driver structure
 * @return errno if error, 0 otherwise
 */
int valve_init(struct valve *v, struct valve_driver *drv);

#ifdef __cplusplus
}
#endif

#endif // __VALVE_H

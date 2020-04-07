#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "valve_driver.h"

struct valve_console_priv {
    bool cached_state; /* false means closed, true means open */
};

static int valve_console_open(struct valve_driver* drv)
{
    struct valve_console_priv *priv = (struct valve_console_priv*) drv->priv;

    if (priv->cached_state) {
        priv->cached_state = !priv->cached_state;
        printf("Valve opened\n");
    } else {
        printf("Valve already open");
    }

    return 0;
}

static int valve_console_close(struct valve_driver* drv)
{
    struct valve_console_priv *priv = (struct valve_console_priv*) drv->priv;

    if (priv->cached_state) {
        priv->cached_state = !priv->cached_state;
        printf("Valve closed\n");
    } else {
        printf("Valve already closed");
    }

    return 0;
}

static int valve_console_get_state(const struct valve_driver* drv, bool *value)
{
    struct valve_console_priv *priv = (struct valve_console_priv*) drv->priv;

    *value = priv->cached_state;

    return 0;
}

static int valve_console_priv_init(struct valve_driver *drv)
{
    struct valve_console_priv *priv = (struct valve_console_priv*) drv->priv;

    priv->cached_state = false;

    return 0;
}

int valve_console_init(struct valve_driver *drv)
{
    int ret;

    if (!drv) {
        return -EINVAL;
    }

    drv->open = valve_console_open;
    drv->close = valve_console_close;
    drv->get_state = valve_console_get_state;

    drv->priv = (struct valve_console_priv*) malloc(sizeof(struct valve_console_priv));
    if (!drv->priv) {
        ret = -ENOMEM;
        goto nomem;
    }

    return valve_console_priv_init(drv);
nomem:
    free(drv);
    return ret;
}

void valve_console_deinit(struct valve_driver *drv)
{
    if (!drv)
        return;
    free(drv->priv);
}
